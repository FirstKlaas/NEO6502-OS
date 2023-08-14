# Commands

## 0x15 Draw horizontal line
Draws a horizonzal line starting at a defined coordinate with
a certain lenght in a given color.

As the screen has width of 320 pixel, we need 16 bit for the
x position and also 16 bit for the length. 

### Parameter
| Register   | Description                               |
| -          | -                                         |
| DIS00      | X position (low byte) in screen pixel     |
| DIS01      | X position (hugh byte) in screen pixel    |
| DIS02      | Y position in screen pixel                |
| DIS03      | Length in pixel (low byte)                |
| DIS04      | Length in Pixel (high byte)               |
| DIS05      | Color index                               |  

## 0x18  Get current background color
Get the background color by index

### Parameter
| Register        | Decription                                |
| -               | -                                         |
| DIS00           | The palette index of the current bgcolor. |


## 0x19  Set current background color
Set the background color by index

### Return
| Register        | Decription                                |
| -               | -                                         |
| DIS00           | The palette index of the current bgcolor. |
