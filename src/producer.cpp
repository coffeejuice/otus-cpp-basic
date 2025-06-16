#include "producer.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <filesystem>
#include "constants.h"

namespace list {
    void work_producer(WorkQueue& queue, std::atomic<bool>& stop_flag) {

        // Create directory if it doesn't exist
        std::filesystem::create_directories(std::filesystem::path(watchDirectory));

        std::wcout << L"Starting file watcher for directory: " << watchDirectory << std::endl;

        // Open directory handle
        HANDLE hDir = CreateFileW(
            watchDirectory.c_str(),
            FILE_LIST_DIRECTORY,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            NULL,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS,
            NULL
        );

        if (hDir == INVALID_HANDLE_VALUE) {
            std::wcerr << L"Failed to open directory: " << watchDirectory
                       << L" Error: " << GetLastError() << std::endl;
            return;
        }

        // Buffer for ReadDirectoryChangesW
        constexpr DWORD bufferSize = 4096;
        char buffer[bufferSize];
        DWORD bytesReturned;

        while (!stop_flag) {
            // Read directory changes
            BOOL result = ReadDirectoryChangesW(
                hDir,
                buffer,
                bufferSize,
                TRUE, // Watch subdirectories
                FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE,
                &bytesReturned,
                NULL,
                NULL
            );

            if (!result) {
                DWORD error = GetLastError();
                if (error == ERROR_OPERATION_ABORTED) {
                    // Normal shutdown
                    break;
                }
                std::wcerr << L"ReadDirectoryChangesW failed with error: " << error << std::endl;
                break;
            }

            if (bytesReturned == 0) {
                continue;
            }

            // Process the changes
            FILE_NOTIFY_INFORMATION* pNotify = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(buffer);

            while (true) {
                // Convert filename from wide char to string
                std::wstring filename(pNotify->FileName, pNotify->FileNameLength / sizeof(WCHAR));

                // Check if file has .KEY extension
                if (filename.size() >= 4) {
                    std::wstring extension = filename.substr(filename.size() - 4);
                    std::transform(extension.begin(), extension.end(), extension.begin(), ::towlower);

                    if (extension == L".key") {
                        // Create full path
                        std::wstring fullPath = watchDirectory + L"\\" + filename;

                        // Convert to narrow string for queue
                        std::string fullPathStr;
                        int size = WideCharToMultiByte(CP_UTF8, 0, fullPath.c_str(), -1, nullptr, 0, nullptr, nullptr);
                        if (size > 0) {
                            fullPathStr.resize(size - 1);
                            WideCharToMultiByte(CP_UTF8, 0, fullPath.c_str(), -1, &fullPathStr[0], size, nullptr, nullptr);
                        }

                        // Check what kind of change occurred
                        const char* changeType = "UNKNOWN";
                        switch (pNotify->Action) {
                            case FILE_ACTION_ADDED:
                                changeType = "ADDED";
                                break;
                            case FILE_ACTION_REMOVED:
                                changeType = "REMOVED";
                                break;
                            case FILE_ACTION_MODIFIED:
                                changeType = "MODIFIED";
                                break;
                            case FILE_ACTION_RENAMED_OLD_NAME:
                                changeType = "RENAMED_OLD";
                                break;
                            case FILE_ACTION_RENAMED_NEW_NAME:
                                changeType = "RENAMED_NEW";
                                break;
                        }

                        std::cout << "File " << changeType << ": " << fullPathStr << std::endl;

                        // Only push to queue for new and modified files (not removed)
                        if (
                            // pNotify->Action == FILE_ACTION_ADDED ||
                            pNotify->Action == FILE_ACTION_MODIFIED
                            // || pNotify->Action == FILE_ACTION_RENAMED_NEW_NAME
                            ) {

                            // For this template, we'll push a hash of the path as an integer
                            // In a real implementation, you might want to change WorkQueue to handle strings
                            // std::hash<std::string> hasher;
                            // int pathHash = static_cast<int>(hasher(fullPathStr));

                            if (!stop_flag) {
                                queue.push(fullPathStr);
                                std::cout << "Pushed to queue: " << fullPathStr << std::endl;
                            }
                        }
                    }
                }

                // Move to next notification
                if (pNotify->NextEntryOffset == 0) {
                    break;
                }
                pNotify = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(
                    reinterpret_cast<char*>(pNotify) + pNotify->NextEntryOffset
                );
            }
        }

        CloseHandle(hDir);
        std::cout << "work_producer - directory watcher stopped" << std::endl;
    }
}