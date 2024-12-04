<img src="assets/logo.png" width="200" height="auto" alt="unt honors logo">

# C Compiler Lexical Analyzer 🚀

## 📝 Table of Contents
- [Project Overview](#-project-overview)
- [Project Background](#-project-background)
- [Objectives](#-project-objectives)
- [Features](#-key-features)
- [Technologies](#-technologies-used)
- [Getting Started](#-getting-started)
- [Usage](#-usage)
- [System Architecture](#-system-architecture)
- [Contributing](#-contributing)
- [License](#-license)
- [Contact](#-contact)
- [Acknowledgements](#-acknowledgements)

## 🚀 Project Overview

A robust lexical analyzer for C programming language, designed to convert raw source code into meaningful tokens for compiler processing.

<img src="assets/Picture1.png" width="400" height="auto" alt="lexer workflow">

## 🔍 Project Background

A lexical analyzer (lexer) is a crucial component of a compiler that performs the following key functions:
- Scans source code character by character
- Groups characters into predefined token sets
- Prepares tokens for syntax analysis in subsequent compiler stages

<img src="assets/Picture2.png" width="200" height="auto" alt="lexer process">

## 🎯 Project Objectives

The primary goals of this lexical analyzer include:
- Converting abstract character streams into meaningful tokens
- Supporting comprehensive C language syntax parsing
- Providing efficient and accurate token generation
- Implementing robust error handling and debugging mechanisms

## ✨ Key Features

### Comprehensive Token Recognition
- Identifies various C language tokens
- Supports multiple comment styles
- Handles whitespace and special characters

### Flexible Input Handling
- Supports standard input
- File-based input processing
- Debugging mode capabilities

### Advanced Parsing Mechanisms
- Finite state machine implementation
- Character-level analysis
- Line and column tracking

## 💻 Technologies Used

- **Programming Language**: C
- **Parsing Technique**: Finite State Machine
- **Development Tools**: 
  - GCC Compiler
  - Valgrind (for memory debugging)
  - Make (build automation)


## 🛠 System Requirements

### Hardware Requirements
- Minimum RAM: 2 GB
- Processor: x86_64 architecture
- Disk Space: 100 MB

### Software Prerequisites
- GCC Compiler (version 7.0+)
- GNU Make
- Linux/Unix environment (recommended)
  
## Getting Started

### Installation

1. Clone the repository
```bash
git clone https://github.com/yourusername/lexical-analyzer.git
cd lexical-analyzer
```

2. Compile the project
```bash
make
```

## 🔧 Usage
### Basic Usage
```bash
./lexer input_file.c
```

### Debugging Mode
```bash
./lexer -d input_file.c
```

# 🏗️ System Architecture

<img src="assets/Picture3.png" width="500" height="auto" alt="lexer workflow">

## Lexer Components

### Input Buffer

- Temporary storage for source code
- Preprocesses input (comment removal)
- Manages file reading efficiently


### Tokenizer

- Converts character streams to tokens
- Tracks line and column positions
- Supports multiple token types


### Token Types

- Identifiers
- Keywords
- Operators
- Literals
- Special Symbols

# Demo Results 

## Basic Arithmetic Operations
<img src="assets/Picture4.png" width="300" height="auto" alt="lexer workflow">
<img src="assets/Picture5.png" width="300" height="auto" alt="lexer workflow">

## Complex Operations 
<img src="assets/Picture7.png" width="300" height="auto" alt="lexer workflow">
<img src="assets/Picture8.png" width="300" height="auto" alt="lexer workflow">

## Entire Source Code
<img src="assets/Picture6.png" width="300" height="auto" alt="lexer workflow">


# Video Demo 

[Demo Video] https://www.youtube.com/watch?v=vd4PzbtRP8U



# 🤝 Contributing

- Fork the repository
- Create your feature branch (git checkout -b feature/AmazingFeature)
- Commit your changes (git commit -m 'Add some AmazingFeature')
- Push to the branch (git push origin feature/AmazingFeature)
- Open a Pull Request

# 📄 License

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/yourusername/lexical-analyzer)
[![Language](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Distributed under the MIT License. See LICENSE for more information.


# 👥 Contact

Bemnet Mekrebu - bemnetmerkebu17@gmail.com

Project Link: [https://github.com/yourusername/lexical-analyzer](https://github.com/bartheart/Lexical-Analyzer-in-C-Honors-College-project-.git)

# 🙏 Acknowledgements

- Dr. Tejasvi Parupudi (Project Supervisor)
- CSCE 3600 Class, Spring 2023





