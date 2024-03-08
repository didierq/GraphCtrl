topic "GraphElementCtrl_Base";
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
[ {{10000@(113.42.0) [s0;%% [*@7;4 Class  GraphElementCtrl`_Base]]}}&]
[s1;:noref: [@(0.0.255)3 template][3 _<][@(0.0.255)3 class][3 _][*@4;3 TYPES][3 , 
][@(0.0.255)3 class][3 _][*@3;3 BASE][3 >]&]
[s1;:Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_Base`:`:class: [@(0.0.255) class]_[* Graph
ElementCtrl`_Base]_:_[@(0.0.255) public]_[*@3 BASE]&]
[s2;%% Base class for ALL GraphElementCtrl classes&]
[s3; &]
[s0;i448;a25;kKO9;@(0.0.255) &]
[ {{10000F(128)G(128)@1 [s0;%% [* Function List]]}}&]
[s0;i448;a25;kKO9;:noref:@(0.0.255) &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Method List]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_Base`:`:OpenPropertiesDlg`(`): [@(0.0.255) v
oid] [* OpenPropertiesDlg]()&]
[s2;%% Method to be called when wanting to open Element Properties 
dialog.&]
[s2;%% By default it is called on Mouse Left Double click&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_Base`:`:openPropertiesDlgCB: [_^Upp`:`:Function^ F
unction]<[@(0.0.255) void]()>_[* openPropertiesDlgCB]&]
[s2;%% &]
[s2;%% This Callback is called to open the per GraphElement properties 
editor dialog.&]
[s2;%% To enable you`'re own properties dialog class, intialize this 
callback in the constructor of you`'re Graph Element by using 
[%-^topic`:`/`/GraphCtrl`/src`/CRTPGraphElementCtrl`_Base`$en`-us`#GraphElementCtrl`_Base`:`:TOpenPropertiesDlg`(void`)^ T
OpenPropertiesDlg()] helper method&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_Base`:`:makePropertiesCtrl: [_^Upp`:`:GraphDraw`_ns`:`:MakeGEPropEditorCtrlFunction^ M
akeGEPropEditorCtrlFunction]_[* makePropertiesCtrl]&]
[s2;%% Callback that creates a new Property editor dialog&]
[s2;%% [%-*@3 v] : Value() tha contains the address of the style to 
modify.&]
[s2;%% The utility template mehod [%-^topic`:`/`/GraphCtrl`/src`/CRTPGraphElementCtrl`_Base`_en`-us`#Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_Base`:`:TMakePropertiesCtrl`(Upp`:`:Value`&`)^ T
MakePropertiesCtrl<EC, DLG<>>()][%-  ]can be used to build the 
CB creating a properies editor dialog.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_Base`:`:TOpenPropertiesDlg`(GE`&`,const STYL`*`*`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 STYL], [@(0.0.255) class]_[*@4 GE]>_[@(0.0.255) void]_[* TO
penPropertiesDlg]([*@4 GE][@(0.0.255) `&]_[*@3 lmnt], [@(0.0.255) const]_[*@4 STYL][@(0.0.255) `*
`*]_[*@3 pStyle])&]
[s2;%% [%-*@3 lmnt] : GraphElement which properties are to modify&]
[s2;%% [%-*@3 pStyle] : current style applied that may also be modified 
in editor&]
[s2;%% Template method that opens the per GraphElement properties 
editor dialog.&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_Base`:`:TMakePropertiesCtrl`(Value`&`): [@(0.0.255) t
emplate] <ELEMENT`_CTRL> ElementPropertiesDlgInterface [@(0.0.255) `*][* TMakePropert
iesCtrl](Value[@(0.0.255) `&] [*@3 v])&]
[s2;%% Utility method that builds a dialog using the passed template 
types. This method is intended to be used build a callback to 
put in [^topic`:`/`/GraphCtrl`/src`/CRTPGraphElementCtrl`_Base`_en`-us`#Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_Base`:`:MakePropertiesCtrl^ M
akePropertiesCtrl() ]&]
[s2;%% [%-*@4 ELEMENT`_CTRL: ]GraphElementCtrl&]
[s2;%% [%-*@4 DLG:] dialog class&]
[s2;%% [%-*@3 v] : Value() tha contains the address of the style to 
modify. the pointer is of type [%-*@4 ELEMENT`_CTRL][* `::StyleGE]`*&]
[s2;%% Returns pointeur to the created Dialog.&]
[s2;%% Note : the created dialog must deleted when finished&]
[s2;%% &]
[s2;%% `_B`::MakePropertiesCtrl `= `[`=`](Value`& v) `->ElementPropertiesDlgInterface`*
 `{ return `_B`::template TMakePropertiesCtrl<CLASSNAME>(v); `};&]
[s2;%% &]
[s3; &]
[s0;%% &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor detail]]}}&]
[s4; &]
[s0; &]
[s0;%% ]]