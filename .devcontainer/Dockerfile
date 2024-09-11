ARG RELEASE_VERSION=release-v5.3

FROM espressif/idf:${RELEASE_VERSION}

ARG DEBIAN_FRONTEND=nointeractive
ARG CONTAINER_USER=esp
ARG USER_UID=1000
ARG USER_GID=$USER_UID

ENV LC_ALL=C.UTF-8
ENV LANG=C.UTF-8

# Install system dependencies
RUN apt-get update \
  && apt install -y -q \
    libnuma1 \
    udev \
  && rm -rf /var/lib/{apt,dpkg,cache,log}/

## Set up udev rules for MCUs pluggin in
# See Also: https://stackoverflow.com/questions/54802684/docker-not-seeing-usb-dev-ttyacm0-after-unplugging-and-then-replugging#:~:text=You%20can%20also%20automate
RUN curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules | tee /etc/udev/rules.d/99-platformio-udev.rules && \
    echo 'ACTION=="add", RUN+="mknod %N c %M %m"' | tee -a /etc/udev/rules.d/100-mknod-usb.rules && \
    echo 'ACTION=="remove", RUN+="rm %N"' | tee -a /etc/udev/rules.d/100-mknod-usb.rules && \
    echo "\n\nAdded All UDEV Rules!\n"

# Add Container User/Group
RUN groupadd --gid $USER_GID $CONTAINER_USER \
  && adduser --uid $USER_UID --gid $USER_GID --disabled-password --gecos "" ${CONTAINER_USER} \
  && usermod -a -G root $CONTAINER_USER && usermod -a -G dialout $CONTAINER_USER \
  && chmod -R 775 /opt/esp/python_env/ \
  && mkdir -p /home/${CONTAINER_USER}/.vscode-server/ \
  && chown -R ${CONTAINER_USER}:${CONTAINER_USER} /home/${CONTAINER_USER}/.vscode-server/

# Switch to our container User
USER ${CONTAINER_USER}
ENV USER=${CONTAINER_USER}
WORKDIR /home/${CONTAINER_USER}

# Magic to make idf.py env functional
RUN echo "source /opt/esp/idf/export.sh > /dev/null 2>&1" >> ~/.bashrc
