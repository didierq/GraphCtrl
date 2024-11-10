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
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_Base`:`:OpenGEPropertiesDlgCB: Functio
n<[@(0.0.255) void] ()> [* OpenGEPropertiesDlgCB]&]
[s2;%% This Callback is called to open the per GraphElement properties 
editor dialog.&]
[s2;%% To enable you`'re own properties dialog class, intialize this 
callback in the constructor of you`'re Graph Element by using 
[%-^topic`:`/`/GraphCtrl`/src`/CRTPGraphElementCtrl`_Base`$en`-us`#GraphElementCtrl`_Base`:`:TOpenPropertiesDlg`(void`)^ T
OpenGEPropertiesDlg()] helper method.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_Base`:`:MakeGEPropertiesCtrlCB: MakeGE
PropEditorCtrlFunction [* MakeGEPropertiesCtrlCB]&]
[s2;%% Callback that creates a new Property editor dialog that will 
be added in the global Graph properties dialog.&]
[s2; [%% CB will be called with as following : ]MakeGEPropertiesCtrlCB( 
[@3 v] );&]
[s2;%% [%-*@3 v] : Value() that contains the [_ address ]of the style 
to modify.&]
[s2;%% The utility template method [%-^topic`:`/`/GraphCtrl`/src`/CRTPGraphElementCtrl`_Base`_en`-us`#Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_Base`:`:TMakeGEPropertiesCtrl`(Upp`:`:Value`&`)^ T
MakeGEPropertiesCtrl<Element`_Ctrl>()][%-  ]can be used to build 
the CB creating a properties editor dialog.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_Base`:`:OpenGEPropertiesDlg`(`): [@(0.0.255) v
oid] [* OpenGEPropertiesDlg]()&]
[s2;%% Opens the GraphElement Properties dialog.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_Base`:`:TOpenGEPropertiesDlg`(GE`&`,const STYL`*`*`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 STYL], [@(0.0.255) class]_[*@4 GE]>_[@(0.0.255) void]_[* TO
penGEPropertiesDlg]([*@4 GE][@(0.0.255) `&]_[*@3 lmnt], [@(0.0.255) const]_[*@4 STYL][@(0.0.255) `*
`*]_[*@3 pStyle])&]
[s2;%% [%-*@3 lmnt] : GraphElement which properties are to modify&]
[s2;%% [%-*@3 pStyle] : current style applied that may also be modified 
in editor&]
[s2;%% Template method that opens the per GraphElement properties 
editor dialog.&]
[s2;%% &]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_Base`:`:TMakeGEPropertiesCtrl`(Value`&`): [@(0.0.255) t
emplate] <[@(0.0.255) class] ELEMENT`_CTRL> GEPropertiesDlgInterface 
[@(0.0.255) `*][* TMakeGEPropertiesCtrl](Value[@(0.0.255) `&] [*@3 v])&]
[s2;%% [%-*@3 ELEMENT`_CTRL][%-*@4  ]: GraphElementCtrl&]
[s2;%% [%-*@3 v] : Value() tha contains the address of the style to 
modify. the pointer is of type [%- ELEMENT`_CTRL]`::StyleGE`*.&]
[s2;%% [*@3 Returns][* :] pointer to the created Dialog. Ownership is 
also passed so the created dialog must deleted by user code when 
finished.&]
[s2;%% Utility method that builds a GraphElement properties dialog 
for GraphElement of type E[%- LEMENT`_CTRL]. It takes advantage 
of knowing the complete type of the ElementCtrl to process the 
v pointer correctly.&]
[s2;%% This method is intended to be used build a callback to put 
in [^topic`:`/`/GraphCtrl`/src`/CRTPGraphElementCtrl`_Base`_en`-us`#Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_Base`:`:MakePropertiesCtrl^ M
akeGEPropertiesCtrl().]&]
[s2; The ELEMENT`_CTRL template parameter &]
[s2;%% &]
[s3; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor detail]]}}&]
[s4; &]
[s0; &]
[s0;%% ]]