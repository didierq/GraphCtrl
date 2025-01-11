# GraphCtrl

Graphing package that focuses on user actions and customization: GraphElements, grid, styling, Series, Editors, ...

- **GraphDraw**: Graphing core package that has no Ctrl capabilities: it can be used in headless CLI apps (that do not depend on CtrlLib)
- **GraphCtrl**: Brings the GraphCtrl Graphing Ctrl (uses GraphDraw)
- **GraphSeries**: contains packages that implement series used with GraphDraw/GraphCtrl  and Series editors used by GraphCtrl to edit Serie properties. Creating new GraphSeries and GraphSeriesEditors is quite simple : there are **project templates** dedicated to these tasks :)
	-  **GraphSeries/ScatterSeries**: Serie based on ScatterDraw (and therefore brings some of the features of ScatterDraw to GraphCtrl)
	-  **GraphSeries/ScatterSeriesEditors**: Preperties Editor for ScatterSeries
	-  **GraphSeries/SimpleJobSerie**: Simple serie intended for low count series that visualize data points as rect tasks (each data point has it's own display style)
- **examples**: 
	- **examples/GraphCtrl_Demo_GUI**: GraphCtrl Demo application
