Graphs
======
The `crow.dot` graph is generated using `cinclude2dot.pl`.
It was ran the `crowlang/src` directory as follows:
```
cinclude2dot.pl --merge module --groups --include . > ../crow.dot

# SVG generation:
dot -Tsvg crow.dot > crow-dot.svg
neato -Tsvg crow.dot > crow-neato.svg
fdp -Tsvg crow.dot > crow-fdp.svg
sfdp -Tsvg crow.dot > crow-sfdp.svg
```
For anybody using these graphs or reading them, please check the git timestamp to see how out of date they are.
Also note that the png format is nice for simplified viewing but zooming is limited for bigger graphs.
