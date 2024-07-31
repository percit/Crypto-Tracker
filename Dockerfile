FROM ubuntu:22.04 AS os

FROM os AS install_qt

ARG INSTALL_DIR=/root
ARG WORKSPACE_DIR=/workspace
ARG QT_VER=6.4.3
ARG QT_ARCH=gcc_64
ARG QT_MODULES=""
ARG USER_ID=1000

WORKDIR $INSTALL_DIR

RUN apt-get update -qq && DEBIAN_FRONTEND=noninteractive apt-get install cmake \
    libxkbcommon-x11-0 libxrender1 libfontconfig libdbus-1-3 libx11-xcb1 libxext6 libglib2.0-0 \
    mesa-common-dev libxkbcommon-dev libvulkan-dev libegl-dev \
    libxcb-icccm4 libxcb-image0 libxcb-keysyms1-dev libxcb-render-util0 libxcb-shape0 \
    gcc-12 clang-format clang-tidy python3-pip -yq libgtest-dev libgmock-dev g++-12 libstdc++-12-dev \
    ninja-build
RUN pip install -U pip; \
    pip install -U aqtinstall

#Install Qt
RUN aqt install-qt --outputdir /opt/qt linux desktop ${QT_VER} ${QT_ARCH} -m ${QT_MODULES}

ENV PATH /opt/qt/${QT_VER}/gcc_64/bin:$PATH
ENV QT_PLUGIN_PATH /opt/qt/${QT_VER}/gcc_64/plugins/
ENV QML_IMPORT_PATH /opt/qt/${QT_VER}/gcc_64/qml/
ENV QML2_IMPORT_PATH /opt/qt/${QT_VER}/gcc_64/qml/
ENV CMAKE_GENERATOR Ninja

RUN useradd -u "$USER_ID" -ms /bin/bash builder
USER builder

WORKDIR $WORKSPACE_DIR