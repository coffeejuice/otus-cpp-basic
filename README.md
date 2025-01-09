# otus-cpp-basic
OTUS C++ Basic traning by Aleksandr Troshin

> ## Useful links
> - [S.Chacon, B.Straub Pro Git](https://git-scm.com/book/ru/v2)
> - [Connecting to GitHub with SSH](https://docs.github.com/en/authentication/connecting-to-github-with-ssh)


> ## GitHub tips
> - add **/compare** to repository address


> ## Git commands
> - **git config --global user.email "alex.troshin@outlook.com"** - set email for the repository user
> - **git config --global user.name "Alex on Laptop"** - set nickname for the repository user
> - **git branch** - lists all branches, highlites current branch with *
> - **git branch -d branch-name** - delete local branch "branch-name"
> - **git push -d origin branch-name** - delete remote branch "branch-name"
> - **git checkout -b branch-name** - create new branch and switch to it (equivalent to **git branch branch-name** + **git checkout branch-name**)
> - **git add filename.ext** - ask git to watch the file "filename.ext"
> - **git commit -m "commit name"** - add new commit/version to the Git, assign commit's name "commit name"
> - **git commit -a -m "commit name"** - add all modified and deleted content and add new commit
> - **git push --set-upstream origin branch-name** == **git push -u origin branch-name** - create in Github a remote branch "branch-name" and then upload 1st commits/versions to Github into the new remote branch
> - **git push** - upload to Github the 2nd and foolowing commits
> - **git help git**, **git help -a** and **git help -g** - get help on Git commands and subcommands
> - **git checkout main** + **git merge branch-name** - switch to branch "main", then merge "branch-name" branch into "main" one


> ## Shell commands
> - **ls -la** - list directory content including hidden one
> - **touch filename.ext** - create empty text file "filename.ext"
