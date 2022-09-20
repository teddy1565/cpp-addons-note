# C++ addons

## 簡介

There are four different interfaces for a Node.js addons

The raw node.h (C++) which is no interface at all - in this case you will have to deal with different V8/Node.js versions - which is very hard and cumbersome;

The old Node.js Nan (C++) which is still maintained and it allows you to have an uniform C++ API across all Node.js versions - but it requires that your addon is built separately for every Node.js version and does not support worker_threads;

The new napi.h (C) which has an uniform ABI across all versions - meaning that a binary module built for one version will work with all later versions;

The newest Node Addon API (C++) which is a set of C++ classes around napi.h that allows you to use NAPI with C++ semantics. It is fully compatible with napi.h and you can mix the two.
For a new module, Node Addon API is by far the best choice.
