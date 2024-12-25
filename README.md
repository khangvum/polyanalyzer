<h1 align="left">polyanalyzer</h1>

###

<p align="left">A Windows console application that analyzes linear, quadratic, cubic, and quartic functions. It generates the variation table of the function and can provide detailed mathematical insights.</p>

###

<h2 align="left">Features</h2>

###

<ul>
<li>Analyze functions of degree 1 to 4 (linear to quartic).</li>
  <li>Display the variation table of the function.</li>
  <li>With the <code>-v</code> (verbose) switch, calculate and display:
    <ol>
      <li>x-intercepts</li>
      <li>y-intercept</li>
      <li>Domain</li>
      <li>Range</li>
      <li>Extrema (Minima & Maxima)</li>
      <li>Symmetry (Even, Odd, or neither)</li>
    </ol>
  </li>
  <li>Simple, fast, and lightweight console-based interface.</li>
</ul>

###

<h2 align="left">Usage</h2>

###

<pre style="font-family: Consolas, monospace; font-size: 14px; background-color: #eee; padding: 15px; border: 1px solid #ccc; border-radius: 5px; white-space: pre; color: #333;">
        Usage: polyanalyzer [--help] [-hv] [a] [b] [c] [d] [e]
        switches:
                h       help
                v       verbose
        arguments:
                a       coefficient of x⁴
                b       coefficient of x³
                c       coefficient of x²
                d       coefficient of x
                e       indepedent coefficient
</pre>