#!/usr/bin/env bash

automake --add-missing --copy > /dev/null 2>&1
autoreconf --install
