topic "1 - GraphCtrl Basics";
[l288;i1120;a17;O9;~~~.1408;2 $$1,0#10431211400427159095818037425705:param]
[a83;*R6 $$2,5#31310162474203024125188417583966:caption]
[H4;b83;*4 $$3,5#07864147445237544204411237157677:title]
[i288;O9;C2 $$4,6#40027414424643823182269349404212:item]
[b42;a42;2 $$5,5#45413000475342174754091244180557:text]
[l288;b17;a17;2 $$6,6#27521748481378242620020725143825:desc]
[l321;C@5;1 $$7,7#20902679421464641399138805415013:code]
[b2503;2 $$8,0#65142375456100023862071332075487:separator]
[*@(0.0.255)2 $$9,0#83433469410354161042741608181528:base]
[C2 $$10,0#37138531426314131251341829483380:class]
[l288;a17;*1 $$11,11#70004532496200323422659154056402:requirement]
[i417;b42;a42;O9;~~~.416;2 $$12,12#10566046415157235020018451313112:tparam]
[b167;C2 $$13,13#92430459443460461911108080531343:item1]
[i288;a42;O9;C2 $$14,14#77422149456609303542238260500223:item2]
[*@2$(0.128.128)2 $$15,15#34511555403152284025741354420178:NewsDate]
[l321;*C$7;2 $$16,16#03451589433145915344929335295360:result]
[l321;b83;a83;*C$7;2 $$17,17#07531550463529505371228428965313:result`-line]
[l160;*C+117 $$18,5#88603949442205825958800053222425:package`-title]
[2 $$19,0#53580023442335529039900623488521:gap]
[C2 $$20,20#70211524482531209251820423858195:class`-nested]
[b50;2 $$21,21#03324558446220344731010354752573:Par]
[2 $$0,0#00000000000000000000000000000000:Default]
[{_}%EN-US 
[s2;:GraphDraw basicsc: [_@4 GraphCtrl basics]&]
[s0;*^topic`:`/`/GraphDraw`/src`/3`_GraphDraw`$en`-us`#CRTP`_EmptyGraphDraw`:`:class^ &]
[ {{10000@(113.42.0) [s0;:GraphDraw Presentation: [*@7;4 GraphCtrl Presentation]]}}&]
[s0;*@7;4 &]
[s0; [* GraphCtrl]is a package that brings GUI reactivity to the [^topic`:`/`/GraphDraw`/srcdoc`/1`_GraphDraw`_basics`$en`-us`#GraphDraw Presentation^ G
raphDraw][*  ]charting package making it an [* Upp`::Ctrl].&]
[s0; &]
[s0; [* GraphCtrl ]is quite simple and follows a few rules:&]
[s0;i150;O0; All drawing is managed by GraphDraw classes&]
[s0;l160; `=`=> [@6 NO drawing must be done] in GraphCtrl classes&]
[s0;i150;O0; GraphCtrl classes only encapsulate GraphDraw classes.&]
[s0;i150;O0; GraphCtrl classes only deal with GUI interaction&]
[s0;i150;O0; They are all templates so that we can use any base class&]
[s0; &]
[s0; The Ctrl management is focused on managing the features of the 
[^topic`:`/`/GraphDraw`/srcdoc`/1`_GraphDraw`_basics`$en`-us`#GraphDraw Presentation^ G
raphElements ]of a [^topic`:`/`/GraphDraw`/src`/GraphDraw`$en`-us`#Upp`:`:GraphDraw`_ns`:`:CRTP`_EmptyGraphDraw`:`:class^ G
raphDraw][^topic`:`/`/GraphDraw`/src`/GraphDraw`$en`-us`#CRTP`_EmptyGraphDraw`:`:class^ .
]&]
[s0; &]
[s0; Some classes add standard behaviour to [^topic`:`/`/GraphDraw`/srcdoc`/1`_GraphDraw`_basics`$en`-us`#GraphDraw Presentation^ G
raphElements] :&]
[s0;i150;O0; [^topic`:`/`/GraphCtrl`/src`/CRTPGraphElementCtrl`_Base`$en`-us`#Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_Base`:`:class^ G
raphElementCtrl`_Base]&]
[s0;^topic`:`/`/GraphCtrl`/src`/CRTPGraphElementCtrl`_Base`$en`-us`#Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_Base`:`:class^ &]
[s0; [_ GraphElementCtrl decorators:]&]
[s0;i150;O0; [^topic`:`/`/GraphCtrl`/src`/CRTPGraphElementCtrl`_Base`$en`-us`#Upp`:`:GraphDraw`_ns`:`:GraphElementCtrl`_FloatMoveResize`:`:class^ G
raphElementCtrl`_FloatMoveResize]&]
[s0;i150;O0; [^topic`:`/`/GraphCtrl`/src`/CRTPGraphElementCtrl`_Base`$en`-us`#Upp`:`:GraphDraw`_ns`:`:AutoHideElementCtrl`:`:class^ A
utoHideElementCtrl]&]
[s0;^topic`:`/`/GraphCtrl`/src`/CRTPGraphElementCtrl`_Base`$en`-us`#Upp`:`:GraphDraw`_ns`:`:AutoHideElementCtrl`:`:class^ &]
[s0; [_ Specilized GraphElementCtrls :]&]
[s0;i150;O0; [^topic`:`/`/GraphCtrl`/src`/StdGridAxisDrawCtrl`$en`-us`#Upp`:`:GraphDraw`_ns`:`:StdGridAxisDrawCtrl`:`:class^ S
tdGridAxisDrawCtrl]&]
[s0;i150;O0; [^topic`:`/`/GraphCtrl`/src`/StdElementCtrl`$en`-us`#Upp`:`:GraphDraw`_ns`:`:StdLegendCtrl`:`:class^ S
tdLegendCtrl]&]
[s0;i150;O0; [^topic`:`/`/GraphCtrl`/src`/StdElementCtrl`$en`-us`#Upp`:`:GraphDraw`_ns`:`:StdLabelCtrl`:`:class^ S
tdLabelCtrl]&]
[s0;i150;O0; [^topic`:`/`/GraphCtrl`/src`/StdElementCtrl`$en`-us`#Upp`:`:GraphDraw`_ns`:`:DynamicMarkerCtrl`:`:class^ D
ynamicMarkerCtrl]&]
[s0; ]]