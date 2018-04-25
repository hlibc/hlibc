# Git Workflow
The workflow to be used is a Feature Branch Workflow.

## Branches
The branch, master, should be used as the development branch;
no pushes should be performed on master to avoid excessive rebasing on feature branches.

The feature branches should be rebased against master every push;
therefore a force push is necessary for every successive push.

There is no release branch, instead, tagging is used.

## Merging to master
The merge commit message should incorporate the rationale and the name of the feature.

