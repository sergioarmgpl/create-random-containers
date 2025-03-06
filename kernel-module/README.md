# Kernel Module for Listing Processes in Active Docker Containers

This kernel module is designed to list the processes running in active Docker containers on Linux distributions. It provides an interface to interact with the Docker container runtime and retrieve process information.

## Project Structure

```
kernel-module
├── src
│   ├── main.c        # Main implementation of the kernel module
│   └── Makefile      # Makefile for building the kernel module
├── include
│   └── module.h      # Header file with declarations and definitions
├── README.md         # Documentation for the project
└── Kconfig           # Configuration options for the kernel module
```

## Building the Module

To build the kernel module, navigate to the `src` directory and run the following command:

```
make
```

This will compile the `main.c` file and produce a kernel object file (`.ko`).

## Loading the Module

Once the module is built, you can load it into the kernel using the following command:

```
sudo insmod <module_name>.ko
```

Replace `<module_name>` with the name of the compiled module.

## Unloading the Module

To remove the module from the kernel, use the following command:

```
sudo rmmod <module_name>
```

## Usage

After loading the module, it will automatically list the processes running in active Docker containers. You can check the kernel log for the output using:

```
dmesg
```

## Dependencies

Ensure that you have the necessary permissions and that the Docker daemon is running to retrieve the list of active containers and their processes.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.