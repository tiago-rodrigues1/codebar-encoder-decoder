# Codebar Encoder and Decoder

A simple codebar encoder and decoder.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contributors](#contact)

## Introduction
This project provides a simple implementation of a codebar encoder and decoder. It is written primarily in C, with a small portion of the project utilizing Makefile for build automation.

## Features
- Encode data into codebar format (EAN-8).
- Decode codebar data back to its original format.

## Installation
To install and set up this project, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/tiago-rodrigues1/codebar-encoder-decoder.git
    cd codebar-encoder-decoder
    ```

2. Build the project using Make:
    ```sh
    make
    ```

## Usage
To use the encoder and decoder, you can run the compiled executable files. Here are some examples:

### Encoding
```sh
./encoder <identifier> -m <margin> -p <area_size> -a <height> -n <filename>
```

### Decoding
```sh
./decode <filename>
```

## Contributors
- Tiago Rodrigues
- Déborah Macedo