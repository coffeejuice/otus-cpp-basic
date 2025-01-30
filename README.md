# otus-cpp-basic
OTUS C++ Basic traning by Aleksandr Troshin

> ## Useful links
> - [S.Chacon, B.Straub Pro Git](https://git-scm.com/book/ru/v2)
> - [Connecting to GitHub with SSH](https://docs.github.com/en/authentication/connecting-to-github-with-ssh)
> - [cPlusPlus.com](https://cplusplus.com/reference/)
> - [cppReference.com](https://en.cppreference.com/w/)
> - [Recursion](http://cppstudio.com/post/418/)
> - [How to mix C and C++](https://isocpp.org/wiki/faq/mixing-c-and-cpp)
> - [Efficient argument passing in C++11](https://www.codesynthesis.com/~boris/blog/2012/06/19/efficient-argument-passing-cxx11-part1/)
> - [Move semantics and rvalue references in C++11](https://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html)


> ## Git commands
> ### Setup git on new PC
> - **git config --global user.email "alex.troshin@outlook.com"** - set email for the repository user
> - **git config --global user.name "Alex on Laptop"** - set nickname for the repository user
> ### New branch
> - **git checkout -b homework_01** - create new branch and switch to it (equivalent to **git branch homework_01** + **git checkout homework_01**)
> - **git push --set-upstream origin homework_01** - create in Github a remote branch "homework_01" and then upload 1st commits/versions to Github into the new remote branch
> ### New commit
> - **git add filename.ext** - ask git to watch the file "filename.ext"
> - **git commit -m "commit name"** - add new commit/version to the Git, assign commit's name "commit name"
> - **git commit -a -m "commit name"** - add all modified and deleted content and add new commit
> ### Other
> - **git branch** - lists all branches, highlites current branch with *
> - **git brnch -d homework_01** - delete branch "homework_01"
> - **git push** - upload to Github the 2nd and foolowing commits
> - **git help git**, **git help -a** and **git help -g** - get help on Git commands and subcommands
> - **git checkout main** + **git merge homework_01** - switch to branch "main", then merge "homework_01" branch into "main" one


> ## Shell commands
> - **ls -la** - list directory content including hidden one
> - **touch filename.ext** - create empty text file "filename.ext"

> ## VScode setup
> - [Install VSCode](https://code.visualstudio.com/docs/setup/windows#_install-vs-code-on-windows)
> - [Configure VS Code for Microsoft C++](https://code.visualstudio.com/docs/cpp/config-msvc)
> - Run 'Developer Command Prompt for Visual Studio'
> - Type in 'code' to open VSCode in the folder

> ## CMake setup
> - [Install CMake](https://cmake.org/download/)
