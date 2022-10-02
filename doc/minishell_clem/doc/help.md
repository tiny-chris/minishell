
#           HELP


#INDEX
------
##  RECIPES
###     WORKFLOW
###     RECOVERY
##  ISSUES
##  GIT

##  POST-IT

Make a feature branch replace the main:
    git checkout feature_branch
    git merge -s ours --no-commit master
    git commit      # Add a message regarding the replacement that you just did
    git checkout master
    git merge feature_branch

##  RECIPES

###     WORKFLOW

* Choose an issue, create a branch, **FIX** the issue…

* Copy the issue into clipboard and remove it from `issues.md`.

* Add/commit/*check*/push all changes:
    $ git add .
    $ git commit
> Commit message according to the issue title and body (paste from clipboard).

Quicklook on the changes that've been made before to push:
    $ git diff main..my-branch
> Use 'git commit --amend' last commit modif needed.

# --------- IF Merge ------------
    $ git push --set-upstream origin my-branch
> Or `$ git push` if not first push.

* Move to 'main' and update it:
    $ git switch main
    $ git pull
* Merge:
    $ git merge my-branch
# ===============================

# --------- IF Rebase -----------
***WARNING*** ONLY if my-branch is LOCAL and haven't been pushed.

* Target rebase destination branch:
    git rebase main
* Move to 'main' and update it:
    $ git switch main
    $ git pull
* Merge:
    git merge my-branch
# ===============================

# --------- IF Conflict ---------
In case of conflicts:

* Manually fix the conflicts then commit the result:
    $ git status
> 'Unmerged paths' files
    <<<<<<< HEAD
    Here is 'main' version
    =======
    Here is 'my-branch' version
    >>>>>>> my-branch

    $ git add .
    $ git commit
> Do not change the commit title but feel free to add details about the merge
> in the body if needed.

# ===============================

# --------- IF Merge ------------
* Delete my-branch:
    $ git push origin --delete my-branch
    $ git branch -d my-branch
# ===============================

# --------- IF Rebase -----------
* Delete my-branch:
    $ git branch -d my-branch
# ===============================

* Push main:
    $ git push

###     RECOVERY

1. Copy (to clipboard) the commit hash of the repo state you want recover:
    $ git log

2. Create a branch and checkout to the desired commit:
    $ git branch my-recovery-branch
    $ git switch my-recovery-branch
    $ git checkout <commit_hash> .
> **Dont forget the '.'** or we go for a detached head stat in which we can make
> changes and commit but nothing will be saved and any commit will be lost as it
> doesnt belong to any branch.

3. Finally, we can add/commit changes:
    git add .
    git commit -m "Reverting to <commit_hash> because..."
    git push

4. Merge main with the branch:

Switch from the branch to 'main' and update it:
    $ git switch main
    $ git pull

Merge 'main' with the branch:
    $ git merge my-recovery-branch
Manually fix the conflicts then commit the result:
    $ git status
> 'Unmerged paths' files are the conflicted.
    <<<<<<< HEAD
    Here is 'main' version
    =======
    Here is 'my-recovery-branch' version
    >>>>>>> my-branch

    $ git add .
    $ git commit
> Do not change the commit title but feel free to add details about the merge in
> the body if needed.

5. Push main and delete the branch:
    $ git push
    $ git push origin --delete my-recovery-branch
    $ git branch -d my-recovery-branch

##  ISSUES

**Issues** title verbs are *imperative*, start with a *Maj* and no '.' in
the title, like this:

- Issue/Commit message *title* (action + subject).
> Issue/Commit message *body*: any details about the issue or to reproduce it.
> Can be multiline

**Commit** message should be exact *copy/paste of the issue* without
the '-' and '>' chars, and without temporary notes in the title
like: '(parsing?or exec?)'.
Title and Body should be separated with *one blank line*.

 If the issue has a body, use `git commit` instead `git commit -m`.

**Tasks** must be organized from top to bottom (*priority at the top*).
Tasks that concern the *same subject* must be *close to each other*.

*Completed task* can be removed from todo.md with '*dap*' (vim normal
mode).

##  GIT

**General:**

*Pull* when we have unstaged modified files:
    git stash
    git pull
    git stash pop

*Transfert uncommited changes* made in a wrong branch to the right branch:
    git stash
    git switch my-right-branch
    git stash apply

*Update the last commit* instead of creating a new one:
    git commit --amend
> Only work if not pushed yet***!!***
> Also useful when we want to fix the last commit message if there is
> a typo.

*Uncommit* unwanted file (remove the last commit without to lost the changes):
    git reset --soft HEAD~1
> Only work if not pushed yet***!!***
> Then `git reset` the unwanted files and commit again with `-c` flag
> to preserve the prev commit message.

*Explore commit* history:

Quick look (one commit per line + graph):
     git log --oneline  --graph --all
More in depth (detail of all modified files + author):
     git log --pretty=format:"%an %cr : %s" --stat --graph -2

**Manage branches:**

*Create* a new branch (don't switch to it):
    git branch <branch_name>

*Delete* a branch (has to be done from another branch):
1. Delete the remote branch
    git push origin --delete <branch_name>
2. Delete the local
    git branch -d <branch_name>

*Switch* to a branch:
    git switch <branch_name>
> Same as 'git checkout <branch_name>

*Diff* two branches:
    git diff <branch1>..<branch2>

Switch to the *previous* branch.
    git switch -

Fully *rename* a branch name
> Except master, which needs few more steps
1. rename the local branch
    git branch --move <wrong_name> <correct_name>
2. rename the remote branch ( update the upstream branch )
    git push -u <remote_name> <correct_name>
3. now remove the still existing local wrong_name
    git push <remote_name> --delete <bad_branch_name>

*List* existing branches:
    git branch
*List ALL* existing branches:
    git branch -a
Shows the last *commit* of each branches:
    git branch -v

**Merge the branch:**

Specify mergetool:
    git mergetool --tool=vimdiff
> Vimdiff recap: 'do' to obtain from the other window, 'dp' to put
> into the other side.

Diff a branch with HEAD:
    git diff <branch_name>

Merge branch_name with the current branch:
    git merge <branch_name>
> If there is a *conflict*, `git status` to see unmerged files, manually
> fix them then `git add` / `git commit -a`.  + describe my merge in
> the commit message.

**Branching Rebasing**

***ONLY rebase local commits that haven't been pushed!***

> Take all the changes that were committed on one
> branch and replay them on a different branch.

1. Rebase 'my-branch' with main (from my-branch):


Target the rebase destination branch:
    git rebase main

Move to the rebase destination branch and merge:
    git switch main
    git merge my-branch

Rebasing example, from 'experiment' to 'master':
1. move to the branch to rebase
    git switch experiment
2. target the rebase destination branch
    git rebase master
3. move to the rebase destination branch
   for a *fast-forward merge*
    git switch master
    git merge experiment

> If master has not diverged, instead of creating
> a 'merge commit', git will just point master to the
> latest commit of the feature branch: *fast-forward*

> There is no difference between the end product
> commit of a rebasing or a merging, but rebasing
> makes a *cleaner history*, a linear one.
