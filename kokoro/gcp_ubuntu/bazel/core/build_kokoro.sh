#!/bin/bash

# Copyright 2020 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Build and test IREE's core within the gcr.io/iree-oss/bazel image using
# Kokoro.

set -e
set -x

# Print the UTC time when set -x is on
export PS4='[$(date -u "+%T %Z")] '

# Kokoro checks out the repository here.
WORKDIR="${KOKORO_ARTIFACTS_DIR?}/github/iree"

# Create a home directory for Bazel
# Bazel creates the build output directory in the user HOME by default. You can
# pass it a startup flag to control this, but then we'd have to make the Bazel
# build script know about Docker/Kokoro nonsense.
HOME="${KOKORO_ROOT?}/home"
mkdir -p "${HOME?}"

declare -a docker_run_args
docker_run_args=(
  # Mount the Kokoro directory
  --volume="${KOKORO_ROOT?}:${KOKORO_ROOT?}"
  # Kokoro checks out the repository here
  --workdir="${KOKORO_ARTIFACTS_DIR?}/github/iree"
  # Run as the current user so that they own any files created.
  --user="$(id -u):$(id -g)"
  # Bazel gets upset if it can't figure out USER. Since the user id we're using
  # isn't registered in the docker container, it otherwise won't be able to
  # figure this out.
  -e USER="$(id -u)"
  # Bazel needs to know this. See above.
  -e HOME="${HOME?}"
  --rm
  gcr.io/iree-oss/bazel:latest
  kokoro/gcp_ubuntu/bazel/core/build.sh
)

# Mount the checked out repository, make that the working directory and run the
# tests in the bazel image.
docker run "${docker_run_args[@]?}"

# Kokoro will rsync this entire directory back to the executor orchestrating the
# build which takes forever and is totally useless.
rm -r "${KOKORO_ARTIFACTS_DIR?}"/*

# Print out artifacts dir contents after deleting them as a coherence check.
ls -1a "${KOKORO_ARTIFACTS_DIR?}/"
