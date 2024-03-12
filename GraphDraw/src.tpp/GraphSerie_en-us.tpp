topic "GraphSeries";
[i448;a25;kKO9;2 $$1,0#37138531426314131252341829483380:class]
[l288;2 $$2,2#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[H6;0 $$4,0#05600065144404261032431302351956:begin]
[i448;a25;kKO9;2 $$5,0#37138531426314131252341829483370:item]
[l288;a4;*@5;1 $$6,6#70004532496200323422659154056402:requirement]
[l288;i1121;b17;O9;~~~.1408;2 $$7,0#10431211400427159095818037425705:param]
[i448;b42;O9;2 $$8,8#61672508125594000341940100500538:tparam]
[b42;2 $$9,9#13035079074754324216151401829390:normal]
[2 $$0,0#00000000000000000000000000000000:Default]
[{_} 
[s0;*@7;4%% &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 StyleGS`_base]]}}&]
[s1;:Upp`:`:GraphDraw`_ns`:`:StyleGS`_base`:`:struct: [@(0.0.255)3 struct][3 _][*3 StyleGS`_
base]&]
[s2;%% struct that contains the common styling parameters for GraphSeries.&]
[s2;%% [* StyleGS`_base ]must be the base class for all GraphSerie 
styles&]
[s3; &]
[s0;*@7;4%% &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 GraphSerieEditorInterface]]}}&]
[s1;:Upp`:`:GraphDraw`_ns`:`:GraphSerieEditorInterface`:`:class: [@(0.0.255)3 class][3 _][*3 G
raphSerieEditorInterface]&]
[s2;%% Interface that allows Editor dialog management by GraphCtrl&]
[s2;%% Contains all information needed to manage GraphSeries style 
editors.&]
[s2; It owns the editor Ctrl instance and also holds the callbacks 
( Function<> ) that will be used by GraphCtrl to integrate the 
properties editor Ctrl in the Series Properties Management dialog&]
[s2;%% Each GraphSerie will have an associated [%-* GraphSerieEditorInterface 
]instance.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerieEditorInterface`:`:DeleteDlg: [_^Upp`:`:Function^ F
unction]<[@(0.0.255) void]()>_[* DeleteDlg]&]
[s2;%% Called when the editor dialog instance must be destroyed&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerieEditorInterface`:`:RetrieveFromDlg: [_^Upp`:`:Function^ F
unction]<[@(0.0.255) void]()>_[* RetrieveFromDlg]&]
[s2;%% Called when modifications must be applied to GraphSerie style&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerieEditorInterface`:`:WhenDlgAction: [_^Upp`:`:Function^ F
unction]<[@(0.0.255) void]()>_[* WhenDlgAction]&]
[s2;%% Called every time an action is done in the editor dialog&]
[s3; &]
[s9; &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 GraphSerie]]}}&]
[s1;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:class: [@(0.0.255)3 class][3 _][*3 GraphSerie]&]
[s2;%% Base class for all GraphSerie implementations: it specifies 
the interface to be implemented by custom GraphSerie classes.&]
[s2;%% It enables to have a fully custom data sources that will be 
[* drawn fully custom, as complex as they can be, there is no limitations 
:)]&]
[s2;%% It holds the styling information of the GraphSerie.&]
[s2;%% &]
[s2;%% [*_ Note 1 :] [*@6 All methods use Graph coordinates][*  ]([@6  It 
has no knowledge of screen coordinates ]). This is intended to 
allow sharing of GraphSeries between several Graphs with different 
CoordinateConverter settings (zoom, or scroll are different, 
or LOG10 instead of standard scaling)&]
[s2;%% &]
[s2;%% [*_ Note 2 :] [*@6 All GraphSerie style structs ( MY`_GraphSerie`::StyleGS 
) must have an assignement operator][@6  ]). This is needed to 
allow making copies of the style and reverting changes when editing 
in GraphSerie style editor.&]
[s3; &]
[s0;i448;a25;kKO9;@(0.0.255) &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Method List]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:GetStyleGDS`(`): [@(0.0.255) virtual] 
[_^Upp`:`:GraphDraw`_ns`:`:StyleGS`_base^ StyleGS`_base][@(0.0.255) `&]_[* GetStyleGDS](
)_`=_[@3 0]&]
[s2;%% Returns the style base of the [*_ G]raph[*_ D]raw [*_ S]erie&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:MakeGraphSerieEditorInfo`(`): [@(0.0.255) vi
rtual] [_ GraphSerieEditorInterface][@(0.0.255) `*]_[* MakeGraphSerieEditorInfo]()&]
[s2;%% Returns &]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:GetHashValue`(`)const: [@(0.0.255) virtual] 
[_^Upp`:`:hash`_t^ hash`_t]_[* GetHashValue]()_[@(0.0.255) const]_`=_[@3 0]&]
[s2;%% Returns the Hash value of the GraphSerie. The hash value is 
used to detect change in the GraphSerie : style modifications, 
data change, visibility change, ... whatever.&]
[s2;%% &]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:GetCount`(`)const: [@(0.0.255) virtual] 
[@(0.0.255) unsigned]_[@(0.0.255) int]_[* GetCount]()_[@(0.0.255) const]_`=_[@3 0]&]
[s2;%% Returns the number elements&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:IsCtrlable`(`)const: [@(0.0.255) bool] 
[* IsCtrlable]() [@(0.0.255) const]&]
[s2;%% Returns true if GraphSerie can react to ctrl actions : like 
LeftDown(), RightDown(), ....&]
[s2;%% Note :&]
[s2;i150;O0;%% in order to work, the [^topic`:`/`/GraphDraw`/src`/GraphSerie`_en`-us`#Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:Contains`(const Upp`:`:GraphDraw`_ns`:`:PointGraph`,unsigned int`&`)const^ C
ontains()] method has to be implemented for you`'re GraphSerie&]
[s2;i150;O0;%% [@6 Number of data points must be kept reasonably low] 
in order to keep good performance.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:IsSelectable`(`)const: [@(0.0.255) bool] 
[* IsSelectable]() [@(0.0.255) const]&]
[s2;%% Returns true if GraphSerie can be selected (whole GraphSerie, 
not individual data points of the GraphSerie).&]
[s2;%% Note :&]
[s2;i150;O0;%% GraphSerie [_ does not need to be Ctrlable] to be Selectable.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:IsDataSelectable`(`)const: [@(0.0.255) bool] 
[* IsDataSelectable]() [@(0.0.255) const]&]
[s2;%% Returns true if GraphSerie Data can be selected (individual 
data points of the GraphSerie, not the whole GraphSerie ).&]
[s2;%% Note :&]
[s2;i150;O0;%% GraphSerie [_ does not need to be Ctrlable] to be Selectable.&]
[s2;i150;O0;%% Selection code is called on LeftUp() for one data 
point selection and leftDrag() to do SelectRect selection..&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:HasDataSelected`(`)const: [@(0.0.255) bool] 
[* HasDataSelected]() [@(0.0.255) const]&]
[s2;%% Returns true if serie has data points that are selected or 
if serie is selected.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:GetSelectDataCount`(`)const: [@(0.0.255) uns
igned] [@(0.0.255) int] [* GetSelectDataCount]() [@(0.0.255) const]&]
[s2;%% Return number of data points that are selected.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:IsDataSelected`(unsigned int`)const: [@(0.0.255) b
ool] [* IsDataSelected]([@(0.0.255) unsigned] [@(0.0.255) int] [*@3 dataIndex]) 
[@(0.0.255) const]&]
[s2;%% Returns true if data`[[%-*@3 dataIndex`]] is selected.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:SelectAllData`(`): [@(0.0.255) void] 
[* SelectAllData]()&]
[s2;%% Select all data points of serie (not equivalent to serie selection 
).&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:SelectData`(const MCoordinateConverter`&`,const Vector`&`,bool`): [@(0.0.255) v
oid] [* SelectData]([@(0.0.255) const] MCoordinateConverter[@(0.0.255) `&] 
[*@3 coordConv], [@(0.0.255) const] Vector<[@(0.0.255) unsigned] [@(0.0.255) int]>[@(0.0.255) `&
] [*@3 dataIndexList], [@(0.0.255) bool] [*@3 append] [@(0.0.255) `=] 
[@(0.0.255) false])&]
[s2;%% Select data points of serie that are in [%-*@3 dataIndexList].&]
[s2;%% If [%-*@3 append] `= [* true]: data in list is appended to current 
selected data points&]
[s2;%% If [%-*@3 append] `= [* false]: selection list replaces current 
selection.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:SelectData`(const MCoordinateConverter`&`,RectScreen`,bool`,bool`): [@(0.0.255) u
nsigned] [@(0.0.255) int] [* SelectData]([@(0.0.255) const] MCoordinateConverter[@(0.0.255) `&
] [*@3 coordConv], RectScreen [*@3 rect], [@(0.0.255) bool] [*@3 instersect] 
[@(0.0.255) `=] [@(0.0.255) false], [@(0.0.255) bool] [*@3 append] [@(0.0.255) `=] 
[@(0.0.255) false])&]
[s2; [%% Selects all data points that are in or ][*@3 instersect][%%  with 
][*@3 rect.]&]
[s2;%% If [%-*@3 append ][%- `= ][* true] : selected data will be appended 
to current selection.&]
[s2;%% Returns number of selected data.&]
[s2;%% [_ Note]: this method is used on Mouse Select Rect.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:SelectOneData`(const MCoordinateConverter`&`,RectScreen`,bool`): V
ector<[@(0.0.255) unsigned] [@(0.0.255) int]> [* SelectOneData]([@(0.0.255) const] 
MCoordinateConverter[@(0.0.255) `&] [*@3 coordConv], RectScreen [*@3 rect], 
[@(0.0.255) bool] [*@3 append] [@(0.0.255) `=] [@(0.0.255) false])&]
[s2; [%% Selects data points which intersect with ][*@3 rect. ]&]
[s2;%% If [%-*@3 append ][%- `= ][* true ]: selected data will be appended 
to current selection.&]
[s2;%% Returns the list of data points that were selected.&]
[s2;%% [_ Note]: this method is used on Mouse click select and [%-*@3 rect] 
represents the mouse position and the select radius.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:InvertDataSelection`(`): [@(0.0.255) void] 
[* InvertDataSelection]()&]
[s2;%%  .&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:UnselectData`(const Vector`&`): [@(0.0.255) v
oid] [* UnselectData]([@(0.0.255) const] Vector<[@(0.0.255) unsigned] 
[@(0.0.255) int]>[@(0.0.255) `&] [*@3 dataIndexList])&]
[s2;%%  [%-*@3 dataIndexList] .&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:ClearSelection`(`): [@(0.0.255) void] 
[* ClearSelection]()&]
[s2;%% Clear All selection : Data Serie selection and Serie selection.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:GetDataSelection`(`)const: Vector<[@(0.0.255) u
nsigned] [@(0.0.255) int]> [* GetDataSelection]() [@(0.0.255) const]&]
[s2;%%  .&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:GetInvertedDataSelection`(`)const: Vector<
[@(0.0.255) unsigned] [@(0.0.255) int]> [* GetInvertedDataSelection]() 
[@(0.0.255) const]&]
[s2;%%  .&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:Contains`(const PointGraph`,unsigned int`&`)const: [@(0.0.255) v
irtual bool] [* Contains]([@(0.0.255) const] PointGraph [*@3 p], [@(0.0.255) unsigned] 
[@(0.0.255) int`&] [*@3 pIndexOut]) [@(0.0.255) const]&]
[s2;%% Returns true if [%-*@3 p] is contained by the drawing of an 
element of the data set.&]
[s2;%% This used to determine if mouse cursor is hovering over a 
data element.&]
[s2;%% [%-*@3 pIndexOut : ]returns the index of the first data element 
that contains [%-*@3 p].&]
[s2;%% [*_@6 Note][@6 : Contains() ][*@6 must return very quickly][@6  in 
order to keep GUI fluid. If Contains() cannot return quickly 
then it should be replaced by `'return false;`']&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:Intersects`(const RectGraph`,unsigned int`&`)const: [@(0.0.255) v
irtual bool] [* Intersects]([@(0.0.255) const] RectGraph [*@3 rect], 
[@(0.0.255) unsigned] [@(0.0.255) int`&] [*@3 pIndexOut]) [@(0.0.255) const]&]
[s2;%% Returns [* true ]if the drawing of a data point (data point 
drawing can be complex and big size) intersects or is included 
within [%-*@3 rect].&]
[s2;%% This can be used for data selection for example.&]
[s2;%% [%-*@3 pIndexOut ]: returns the index of the first data element 
that intersects with [%-*@3 rect].&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:PaintSerie`(BufferPainter`&`,const bool`,int`,const MCoordinateConverter`&`): [@(0.0.255) v
irtual void] [* PaintSerie](BufferPainter[@(0.0.255) `&] [*@3 dw], 
[@(0.0.255) const] [@(0.0.255) bool] [*@3 doFastPaint], [@(0.0.255) int] 
[*@3 scale], [@(0.0.255) const] MCoordinateConverter[@(0.0.255) `&] 
[*@3 coordConv])&]
[s2;%% Draw to [%-*@3 dw] all the data at scale : [%-*@3 scale] and using 
[%-*@3 coordConv].&]
[s2;%% If [%-*@3 doFastPaint] is true: the data [_ must be draw very fast] 
even by drawing partial data. The aim is to have fluid scroll 
/ zoom.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:PaintSelected`(BufferPainter`&`,const bool`,int`,const MCoordinateConverter`&`): [@(0.0.255) v
irtual void] [* PaintSelected](BufferPainter[@(0.0.255) `&] [*@3 dw], 
[@(0.0.255) const] [@(0.0.255) bool] [*@3 doFastPaint], [@(0.0.255) int] 
[*@3 scale], [@(0.0.255) const] MCoordinateConverter[@(0.0.255) `&] 
[*@3 coordConv])&]
[s2;%%  [%-*@3 dw] [%-*@3 doFastPaint] [%-*@3 scale] [%-*@3 coordConv] .&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:PaintOne`(unsigned int`,int`,BufferPainter`&`,int`,const MCoordinateConverter`&`)const: [@(0.0.255) v
oid] [* PaintOne]([@(0.0.255) unsigned] [@(0.0.255) int] [*@3 index], 
[@(0.0.255) int] [*@3 style], BufferPainter[@(0.0.255) `&] [*@3 dw], 
[@(0.0.255) int] [*@3 scale], [@(0.0.255) const] MCoordinateConverter[@(0.0.255) `&] 
[*@3 coordConv]) [@(0.0.255) const]&]
[s2; [%% Draw to ][*@3 dw][%%  only one data point with style ][*@3 style 
][%% at scale : ][*@3 scale][%%  and using ][*@3 coordConv.]&]
[s2;%% This method is intended to interact with Ctrl.&]
[s2; [*@3 style : ]CTRL`_NORMAL, CTRL`_HOT, CTRL`_PRESSED, CTRL`_DISABLED, 
CTRL`_CHECKED, CTRL`_HOTCHECKED.&]
[s2; Default implementation available in GraphDraw does not take 
style into account&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:SetAutoColor`(int`,Color`): [@(0.0.255) virt
ual void] [* SetAutoColor]([@(0.0.255) int] [*@3 id], Color [*@3 colorHint])&]
[s2;%% Automatically sets default colors according to [%-*@3 id ]so 
that each data serie automatically has a different color. (color 
`= colorTable`[[%-*@3 id]`])&]
[s2;%% Alternatively, [%-*@3 colorHint] can be used to force the color.&]
[s2;%% If [%-*@3 colorHint] is Null, [%-*@3 id ]must be used&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:HasMinMax`(`)const: [@(0.0.255) virtual] 
[@(0.0.255) bool]_[* HasMinMax]()_[@(0.0.255) const]_`=_[@3 0]&]
[s2;%% Returns [* true ]if X and Y  Min/Max are available. Otherwise 
it returns false&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:MinX`(`)const: [@(0.0.255) virtual] 
[_^Upp`:`:GraphDraw`_ns`:`:TypeGraphCoord^ TypeGraphCoord]_[* MinX]()_[@(0.0.255) const
]_`=_[@3 0]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:MinY`(`)const: [@(0.0.255) virtual] 
[_^Upp`:`:GraphDraw`_ns`:`:TypeGraphCoord^ TypeGraphCoord]_[* MinY]()_[@(0.0.255) const
]_`=_[@3 0]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:MaxX`(`)const: [@(0.0.255) virtual] 
[_^Upp`:`:GraphDraw`_ns`:`:TypeGraphCoord^ TypeGraphCoord]_[* MaxX]()_[@(0.0.255) const
]_`=_[@3 0]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:MaxY`(`)const: [@(0.0.255) virtual] 
[_^Upp`:`:GraphDraw`_ns`:`:TypeGraphCoord^ TypeGraphCoord]_[* MaxY]()_[@(0.0.255) const
]_`=_[@3 0]&]
[s2;%% Return de MIN and MAX values reached by the GraphSerie.&]
[s2;%% This is needed to enable fitting graphs to the data draw.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:ShowLegend`(bool`): [@(0.0.255) void]_[* ShowL
egend]([@(0.0.255) bool]_[*@3 v][@(0.0.255) `=true])&]
[s2;%% Set legend visibility of this GraphSerie&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:IsShowLegend`(`)const: [@(0.0.255) bool]_[* Is
ShowLegend]()_[@(0.0.255) const]&]
[s2;%% Returns [* true ]if legend of this GraphSerie is visible&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:MakeSerieIcon`(int`,const int`)const: [_^Upp`:`:Image^ I
mage]_[* MakeSerieIcon](_[@(0.0.255) int]_[*@3 width][@(0.0.255) `=][@3 16], 
[@(0.0.255) const]_[@(0.0.255) int]_[*@3 scale][@(0.0.255) `=][@3 1]_)_[@(0.0.255) const]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphSerie`:`:MakeSerieIcon`(Size`,const int`)const: [@(0.0.255) v
irtual] [_^Upp`:`:Image^ Image]_[* MakeSerieIcon](_[_^Upp`:`:Size^ Size]_[*@3 sz], 
[@(0.0.255) const]_[@(0.0.255) int]_[*@3 scale]_)_[@(0.0.255) const]&]
[s2;%% Returns an [* alpha] image that can be used as an icon in order 
to display what the Serie looks like.&]
[s2;%% [_ Note]: the [@6 returned image does not have it`'s background 
filled][*@6  ](it is transparent) in order to be displayed with 
the right background.&]
[s2;%% [%-*@3 sz] or [%-*@3 width:] Size of the image returned (16x16 
by default)&]
[s2;%% [%-*@3 scale:] Indicates how the image will be scaled: higher 
scale means higher precision in image. Mostly used to get high 
resolution images when copying whole graphs in order to paste 
them in office documents.&]
[s3;%% &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 CustomData]]}}&]
[s4; &]
[s1;:Upp`:`:GraphDraw`_ns`:`:CustomData`:`:class: [@(0.0.255)3 class][3 _][*3 CustomData]&]
[s2;%% Base class for all custom data: it specifies the interface 
to be implemented by custom data. The objective is to enable 
drawing of arbitrarelly complex data and (not limited to x,y 
and z values).&]
[s2;%% One instance of CustomData represents one data point.&]
[s2;%% A data serie is represented by a collection of CustomData 
( [^topic`:`/`/GraphDraw`/src`/CustomDataSource`_en`-us`#Upp`:`:GraphDraw`_ns`:`:CustomDataSource`:`:class^ C
ustomDataSource ])&]
[s2;%% A CustomData instance only knows (and stores) information 
about the data, logical GraphCoordinates and how to draw the 
data.&]
[s2;%% It [@6 has no knowledge of screen coordinates ]: this allows 
to share CustomData in different series and graphs (saving precious 
memory).&]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Method List]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CustomData`:`:Intersects`(const RectGraph`&`)const: [@(0.0.255) v
irtual] [@(0.0.255) bool]_[* Intersects]([@(0.0.255) const]_[_^Upp`:`:GraphDraw`_ns`:`:RectGraph^ R
ectGraph][@(0.0.255) `&]_[*@3 rect])_[@(0.0.255) const]_`=_[@3 0]&]
[s2;%% Returns TRUE if .data drawing intersect or is included in 
[%-*@3 rect].&]
[s2;%% This is used to determine if a data point must be drawn or 
not (only visible points are drawn) and for selection management&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CustomData`:`:Contained`(const RectGraph`&`)const: [@(0.0.255) v
irtual] [@(0.0.255) bool]_[* Contained]([@(0.0.255) const]_[_^Upp`:`:GraphDraw`_ns`:`:RectGraph^ R
ectGraph][@(0.0.255) `&]_[*@3 rect])_[@(0.0.255) const]_`=_[@3 0]&]
[s2;%% Returns TRUE if the current CustomData drawing is included 
in [%-*@3 rect].&]
[s2;%% This is used to determine if a data point must be drawn or 
not (only visible points are drawn) and for selection management.&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CustomData`:`:Contains`(const PointGraph`&`)const: [@(0.0.255) v
irtual] [@(0.0.255) bool]_[* Contains]([@(0.0.255) const]_[_^Upp`:`:GraphDraw`_ns`:`:PointGraph^ P
ointGraph][@(0.0.255) `&]_[*@3 pt])_[@(0.0.255) const]_`=_[@3 0]&]
[s2;%% Returns TRUE if current CustomData point drawing bounds constains 
[%-*@3 pt].&]
[s2;%% This used to determine if a mouse event is to be distributed 
to the CustomData point and selection management.&]
[s2;%% [_ Note ]: A RectGraph is usualy used as the drawing bounds&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:CustomData`:`:PaintDataPoint`(BufferPainter`&`,int`,int`,const MCoordinateConverter`&`)const: [@(0.0.255) v
irtual] [@(0.0.255) void]_[* PaintDataPoint]([_^Upp`:`:BufferPainter^ BufferPainter][@(0.0.255) `&
]_[*@3 dw], [@(0.0.255) int]_[*@3 scale], [@(0.0.255) int]_[*@3 style], 
[@(0.0.255) const]_[_^Upp`:`:GraphDraw`_ns`:`:MCoordinateConverter^ MCoordinateConver
ter][@(0.0.255) `&]_[*@3 coordConv]_)_[@(0.0.255) const]&]
[s2;%% Paints to [%-*@3 dw ]the CustomData instance at [%-*@3 scale ]and 
using the [%-*@3 coordConv ]to convert to screen coordinates.&]
[s2; [*@3 style ]values are free but the following values are reserved:&]
[s0;l288;i150;O0; [@(255.0.255) DEFAULT`_STYLE    `=  0] : normal drawing 
style.&]
[s2;i150;O0; [@(255.0.255) HIGHLIGHT`_STYLE `= `-1] : Draw the serie 
highlighted&]
[s2;%% &]
[s3;%% &]
[s0;*@7;4%% &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 SimpleGraphSerie]]}}&]
[s1;:Upp`:`:GraphDraw`_ns`:`:SimpleGraphSerie`:`:class: [@(0.0.255)3 class][3 _][*3 SimpleG
raphSerie][3 _:_][@(0.0.255)3 public][3 _][*@3;3 GraphSerie]&]
[s2;%% Helper class intended to ease implementation of GraphSerie 
child classes with the following constraints:&]
[s2;i150;O0;%% Limited number of data points : all is managed and 
not optimized for speed&]
[s2;i150;O0;%% Data used has to be a child CustomData interface class&]
[s2;%% Most important methods are already imlemented but ownership 
(and container) of data is not implemented : it has to be part 
of the user class.&]
[s3; &]
[s0;*@7;4%% &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 SimpleArrayGraphSerie]]}}&]
[s1;:noref: [@(0.0.255)3 template][3 _<][@(0.0.255)3 class][3 _][*@4;3 CUST`_DATA`_TYPE][3 >]&]
[s1;:Upp`:`:GraphDraw`_ns`:`:SimpleArrayGraphSerie`:`:class: [@(0.0.255)3 class][3 _][*3 Si
mpleArrayGraphSerie][3 _:_][@(0.0.255)3 public][3 _][*@3;3 SimpleGraphSerie]&]
[s2; [%% Helper class that adds data storage management (using an Array) 
to ][* SimpleGraphSerie]&]
[s3; &]
[s3; ]]