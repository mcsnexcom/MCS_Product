## build_install_opencv.sh
This script automates the process of building and installing OpenCV version 4.10.0 from source code. Its main purpose is to create a custom OpenCV build specifically configured to use NVIDIA's CUDA and cuDNN libraries, which enables GPU acceleration for computer vision tasks.
  ### **Key points:**
  - Removes any existing OpenCV versions to prevent conflicts.
  - Installs all necessary dependencies, like build tools and libraries for handling various media formats (GStreamer, libv4l, etc.).
  - Downloads the source code for both OpenCV and its companion opencv_contrib repository.
  - Configures and compiles the code with flags that enable support for CUDA, cuDNN, GStreamer, and Python 3.
  - Installs the newly built library and updates system environment variables so applications can find it.

## install_sdk.sh
This script functions as an installer for the NVIDIA JetPack SDK on a compatible device (like an NVIDIA Jetson). It's designed to be run with root privileges.
  ### **Key points:**
  - Checks for prerequisites, ensuring it's run by the root user and that there's at least 10 GB of free disk space.
  - Installs the nvidia-jetpack meta-package, which bundles essential NVIDIA software like CUDA, cuDNN, TensorRT, and others needed for high-performance computing and AI.
  - Optionally installs DeepStream, an SDK for building intelligent video analytics (IVA) pipelines. It finds the available version and asks the user for confirmation before installing it.
