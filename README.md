# polyanalyzer

A Windows console application that analyzes ***linear***, ***quadratic***, ***cubic***, and ***quartic*** functions. It generates the ***variation table*** of the function and can provide detailed ***mathematical insights***.

## Features

-   Analyze functions of degree 1 to 4 (***linear*** to ***quartic***).
-   Display the ***variation table*** of the function.
-   With the verbose (`-v`) switch, calculate and display:
    
    1.  ***x-intercepts***
    2.  ***y-intercept***
    3.  ***Domain***
    4.  ***Range***
    5.  ***Extrema*** (Minima & Maxima)
    6.  ***Symmetry*** (Even, Odd, or neither)

-   Simple, fast, and lightweight ***console-based*** interface.

## Usage

```cmd
Usage: polyanalyzer [--help] [-hv] [a] [b] [c] [d] [e]
switches:
        h       help
        v       verbose
arguments:
        a       coefficient of x⁴
        b       coefficient of x³
        c       coefficient of x²
        d       coefficient of x
        e       independent coefficient
```

## Demonstration

### Without the verbose (`-v`) switch (Default behavior):

![Default Behavior](!docs/Default%20Behavior.png =70%x70%)

### With the verbose (`-v`) switch:

![Verbose](!docs/Verbose.png =70%x70%)