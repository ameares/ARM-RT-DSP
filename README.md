# ARM-RT-DSP (ARM Real-Time DSP Extension Library)

![Project status](https://img.shields.io/badge/Project%20status-Work%20in%20progress-orange)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![GitHub Issues](https://img.shields.io/github/issues/your-username/ARM-RT-DSP)](https://github.com/your-username/ARM-RT-DSP/issues)
[![GitHub Pull Requests](https://img.shields.io/github/issues-pr/your-username/ARM-RT-DSP)](https://github.com/your-username/ARM-RT-DSP/pulls)
![C/C++ CI](https://github.com/ameares/ARM-RT-DSP/workflows/C/C++%20CI/badge.svg?branch=master)

Welcome to the ARM-RT-DSP repository! This repository contains the ARM Real-Time DSP Extension Library, which provides a collection of optimized digital signal processing (DSP) algorithms for ARM-based platforms. The primary focus of the library is to facilitate real-time control applications on ARM processors in conjunction with the ARM DSP support library. The library complements the [ARM CMSIS-DSP](https://github.com/ARM-software/CMSIS-DSP) library.

**Please note:** This project is currently under active development and is not yet ready for use in production environments. The documentation, API, and other aspects may undergo significant changes as the project evolves.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Features

- Primarily designed for real-time control applications.
- Intended for ARM processors but can be used on other platforms.
- Support macros for defining fixed point constants.
- 32-bit saturated math functions.
- Conversion functions for fixed-point data types.
- Limit and range check functions.
- Ramp functions.
- Hysteresis functions.
- Fast and simple pseudo-moving average filter.

## Installation

To use the ARM-RT-DSP library, follow these steps:

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/ARM-RT-DSP.git
   ```

2. Include the necessary library files in your project.

3. Build and link the library files with your project according to your build system.

## Usage

To start using the ARM-RT-DSP library, please refer to the [Usage Guide](docs/usage_guide.md). It provides an overview of the library's modules, functions, and usage examples to help you integrate the library into your projects effectively.

## License

The ARM-RT-DSP library is open-source and released under the [MIT License](LICENSE.md). Feel free to use, modify, and distribute the library in your own projects.

## Contact

For any questions, feedback, or suggestions regarding the ARM-RT-DSP library, please contact:

Andrew Meares
Email: mearesinfo@gmail.com

We appreciate your interest in the ARM-RT-DSP project!
