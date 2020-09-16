FROM gcr.io/iree-oss/util AS final

ARG VULKAN_SDK_VERSION=1.2.141.2

RUN wget -q \
  "https://sdk.lunarg.com/sdk/download/${VULKAN_SDK_VERSION?}/linux/vulkansdk-linux-${VULKAN_SDK_VERSION?}.tar.gz" \
  -O "/tmp/vulkansdk-linux-x86_64-${VULKAN_SDK_VERSION}.tar.gz"
RUN mkdir -p /opt/vulkan
RUN tar -xf /tmp/vulkansdk-linux-x86_64-$VULKAN_SDK_VERSION.tar.gz -C /opt/vulkan
