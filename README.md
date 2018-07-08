# Example SailfishOS App using CMake
This code example shows how to use CMake to build your own SailfishOS application.

## Example 1: Using libsailfishapp
The first example shows a simple and straight-forward approach to build a native SailfishOS application based on libsailfishapp.

## Example 2: Generic application
The second example just shows a customizable SailfishOS without depending on an additional library. While this approach requires some overhead by the developer, it probably integrates better with your existing, multi-platform code base. Other than that, it just shows the difference. You decide which suits your needs best.

### Note for example 2
Currently the declarative booster package is not found by CMake. To workaround this issue, please open the file `cmakesample.desktop` and comment the line `X-Nemo-Application-Type=silica-qt5`.

## Building the examples
The build process is straight-forward. Make sure to meet the following pre-conditions:

1. MerSDK virtual machine is installed and running on your machine.
2. Connect to your MerSDK instance: `ssh -p 2222 -i ~/SailfishOS/vmshare/ssh/private\_keys/engine/mersdk mersdk@localhost`
3. Go to your project folder: e.g. `cd share/projects/cmakesample`

Once you are all set you can build the example:

```bash
# replace version & target with your own strings
export SFOS_TARGET=SailfishOS-2.2.0.29-armv7hl

# build example 1
mb2 -t $SFOS_TARGET build

# build example 2
mb2 -t $SFOS_TARGET build --without libsailfishapp
```

Feel free to play around with the example!
