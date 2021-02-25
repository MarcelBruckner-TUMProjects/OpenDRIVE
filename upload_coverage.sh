#!/bin/bash

teamscale-upload --server http://localhost:8080 --project opendrive --user brucknem --accesskey "$1" --partition "Automatic GCov Upload" --format gcov cmake-build-debug-coverage/coverage/*
