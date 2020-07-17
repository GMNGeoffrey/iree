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

# An image for building IREE using CMake and testing IREE with NVIDIA GPUs.

# Build using:
# docker build --tag gcr.io/iree-oss/cmake-nvidia \
#              build_tools/docker/cmake_nvidia/

# Run interactively using the following, where IREE_WORKDIR is the path to your
# local dev environment:
# docker run -it --rm --entrypoint bash \
#   --volume "${IREE_WORKDIR?}:/usr/src/iree/" \
#   --gpus all \
#   gcr.io/iree-oss/cmake-nvidia

# Set up the image and working directory by inheriting the base
# CMake configuration.
# Note that we don't start from NVIDIA's docker base:
# - nvidia/cuda (https://hub.docker.com/r/nvidia/cuda):
#     it's.. for CUDA.
# - nvidia/vulkan (https://hub.docker.com/r/nvidia/vulkan):
#      does not support Ubuntu 18.04.
# This allows to share configuration with base CMake, but it also means we need
# to MATCH the driver version between the host machine and the docker image.
FROM gcr.io/iree-oss/cmake

# Additionally, we need to install the Vulkan SDK and the NVIDIA Vulkan driver.

ARG VULKAN_SDK_VERSION=1.2.141.2
ARG NVIDIA_DRIVER_VERSION=440.95.01

RUN echo "downloading Vulkan SDK ${VULKAN_SDK_VERSION?}" \
    && wget -q --show-progress --progress=bar:force:noscroll \
      "https://sdk.lunarg.com/sdk/download/${VULKAN_SDK_VERSION?}/linux/vulkansdk-linux-x86_64-${VULKAN_SDK_VERSION?}.tar.gz" \
      -O "/tmp/vulkansdk-linux-x86_64-${VULKAN_SDK_VERSION?}.tar.gz" \
    && echo "installing Vulkan SDK ${VULKAN_SDK_VERSION?}" \
    && mkdir -p /opt/vulkan \
    && tar -xf /tmp/vulkansdk-linux-x86_64-$VULKAN_SDK_VERSION.tar.gz -C /opt/vulkan \
    && rm /tmp/vulkansdk-linux-x86_64-$VULKAN_SDK_VERSION.tar.gz

RUN echo "downloading NVidia ${NVIDIA_DRIVER_VERSION?}" \
    && wget --show-progress --progress=bar:force:noscroll \
      "http://us.download.nvidia.com/tesla/${NVIDIA_DRIVER_VERSION?}/NVIDIA-Linux-x86_64-${NVIDIA_DRIVER_VERSION?}.run" \
      -O "/tmp/NVIDIA-Linux-x86_64-${NVIDIA_DRIVER_VERSION?}.run" \
    && cd /tmp \
    && sh "NVIDIA-Linux-x86_64-${NVIDIA_DRIVER_VERSION?}.run" --extract-only \
    && cp "/tmp/NVIDIA-Linux-x86_64-${NVIDIA_DRIVER_VERSION?}/libnvidia-cbl.so.${NVIDIA_DRIVER_VERSION?}" /usr/lib/x86_64-linux-gnu/ \
    && cp "/tmp/NVIDIA-Linux-x86_64-${NVIDIA_DRIVER_VERSION?}/libnvidia-glvkspirv.so.${NVIDIA_DRIVER_VERSION?}" /usr/lib/x86_64-linux-gnu/ \
    && cp "/tmp/NVIDIA-Linux-x86_64-${NVIDIA_DRIVER_VERSION?}/libnvidia-rtcore.so.${NVIDIA_DRIVER_VERSION?}" /usr/lib/x86_64-linux-gnu/ \
    && rm -r "/tmp/NVIDIA-Linux-x86_64-${NVIDIA_DRIVER_VERSION?}" "/tmp/NVIDIA-Linux-x86_64-${NVIDIA_DRIVER_VERSION?}.run"
