# TODO

* Refactor config to have a union type rather than explicit for the type
  * i.e., consider that RGB is common, and should be the basis type, however we may have HSV that needs to convert.
  ```c
    struct {
        // 0 - 254
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    } rgb;
    struct {
        float hue; // need to find rtos type
        float saturation;
        float value;
    } hsv;

  typedef union {
    struct rgb;
    struct hsv;
  } ColorDefinition;
  ```
* Task to initialize LED ***OFF*** and delay for a configurable time
  * This shouldn't be limited to just initializing the LED, but we should kick it off as such.
  * Could be sub tasks that kill themselves when done... This can get tricky if handled incorrectly 🤔
* Task to BOOT
  * Might need waterfall cascade effect for cleanliness? Maybe not...
  * Initialize LED with some kind of "signature" pattern on boot. This would be used moving forward :P
  * Diagnostics could partake here as well, and also utilize LED or Display to show error
    * Might need to be fleshed out more with a proper boot system in my own app arch, with error handling. This would mean the app could boot into a minimal mode, and retrieve errors from the boot task somehow (or the boot task had previously stored them in the appropriate place for the error handler to get??) and then would handle it accordingly with however the system can.. Again, much much more thought out that needs to happen so that it can determine the state of the system and exactly HOW to figure out health, as well as HOW to figure out reporting.

# NOTES:

From LLM.. I started editing, but gave up so if i use it, need to fix it!

```c
void rgbToHsv(ColorDefinition *color) {
    float r = color->rgb.r / 255.0;
    float g = color->rgb.g / 255.0;
    float b = color->rgb.b / 255.0;

    float max = r > g ? (r > b ? r : b) : (g > b ? g : b);
    float min = r < g ? (r < b ? r : b) : (g < b ? g : b);
    float h, s, v = max;

    float d = max - min;
    s = max == 0 ? 0 : d / max;

    if (max == min) {
        h = 0; // achromatic
    } else {
        if (max == r) {
            h = (g - b) / d + (g < b ? 6 : 0);
        } else if (max == g) {
            h = (b - r) / d + 2;
        } else {
            h = (r - g) / d + 4;
        }
        h /= 6;
    }

    color->hsv.h = h * 360; // Convert to degrees
    color->hsv.s = s;
    color->hsv.v = v;
}

void hsvToRgb(ColorDefinition *color) {
    float h = color->hsv.hue / 360; // Convert to [0, 1]
    float s = color->hsv.saturation;
    float v = color->hsv.value;

    int i = (int)(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);
    i = i % 6;

    switch (i) {
        case 0: color->rgb.red = v * 255; color->rgb.green = t * 255; color->rgb.blue = p * 255; break;
        case 1: color->rgb.red = q * 255; color->rgb.green = v * 255; color->rgb.blue = p * 255; break;
        case 2: color->rgb.red = p * 255; color->rgb.green = v * 255; color->rgb.blue = t * 255; break;
        case 3: color->rgb.red = p * 255; color->rgb.green = q * 255; color->rgb.blue = v * 255; break;
        case 4: color->rgb.red = t * 255; color->rgb.green = p * 255; color->rgb.blue = v * 255; break;
        case 5: color->rgb.red = v * 255; color->rgb.green = p * 255; color->rgb.blue = q * 255; break;
    }
}

int main() {
    Color color;

    // Example RGB color
    color.rgb.r = 255;
    color.rgb.g = 0;
    color.rgb.b = 0;

    // Convert RGB to HSV
    rgbToHsv(&color);
    printf("HSV: (%f, %f, %f)\n", color.hsv.h, color.hsv.s, color.hsv.v);

    // Convert back to RGB
    hsvToRgb(&color);
    printf("RGB: (%d, %d, %d)\n", color.rgb.r, color.rgb.g, color.rgb.b);

    return 0;
}

```
