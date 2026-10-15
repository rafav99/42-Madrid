#!/usr/bin/env bash
set -Eeuo pipefail

cd "$(dirname "$0")"
REPO="https://github.com/rafav99/42-Madrid.git"

echo "[1/5] Importing original sources at pinned commits..."
python3 tools/bootstrap.py

echo "[2/5] Building all seven projects..."
make all

echo "[3/5] Running automated tests..."
make test

echo "[4/5] Checking Git repository and remote..."
if git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
    TOP="$(git rev-parse --show-toplevel)"
    if [ "$TOP" != "$PWD" ]; then
        echo "Refusing to publish inside another repository: $TOP" >&2
        exit 1
    fi
else
    git init -b main
fi
if git remote get-url origin >/dev/null 2>&1; then
    CURRENT="$(git remote get-url origin)"
    if [ "$CURRENT" != "$REPO" ] && [ "$CURRENT" != "git@github.com:rafav99/42-Madrid.git" ]; then
        echo "Refusing to publish to unexpected origin: $CURRENT" >&2
        exit 1
    fi
else
    git remote add origin "$REPO"
fi
if git ls-remote --exit-code --heads origin main >/dev/null 2>&1; then
    echo "Remote main already contains commits. Stop to prevent an accidental overwrite." >&2
    exit 1
fi
if ! git config user.name >/dev/null || ! git config user.email >/dev/null; then
    echo "Configure your Git identity before publishing:" >&2
    echo 'git config --global user.name "Your name"' >&2
    echo 'git config --global user.email "you@example.com"' >&2
    exit 1
fi

echo "[5/5] Committing tested source files and pushing to GitHub..."
git add -A
if git diff --cached --quiet; then
    echo "No changes to commit."
else
    git commit -m "Integrate 42 Madrid projects and shared libraries"
fi
git branch -M main
git push -u origin main
echo "Published: https://github.com/rafav99/42-Madrid"
