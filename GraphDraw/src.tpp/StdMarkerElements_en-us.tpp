topic "Marker Management";
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
[ {{10000@(113.42.0) [s0;%% [*@7;4 MarkerElementData class]]}}&]
[s0;%% &]
[s1;:Upp`:`:GraphDraw`_ns`:`:MarkerElementData`:`:class: [@(0.0.255)3 class][3 _][*3 Marker
ElementData][3 _:_][@(0.0.255)3 private][3 _][*@3;3 Moveable][3 <][*3 MarkerElementData][3 >_]&]
[s2;%% This class is a container for MarkerData:&]
[s2;i150;O0;%% Marker position value&]
[s2;i150;O0;%% Marker drawing instance used&]
[s2;i150;O0;%% Marker ID: only NON NEGATIVE values are valid&]
[s2;%% &]
[s2;%% [*@3 INVALID`_MARKER`_ID] (`=`-1) enum value can be used to 
manage INVALID VALUES&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:MarkerElementData`:`:GetTickMark`(`)const: [_^topic`:`/`/GraphDraw`/src`/TickMark`$en`-us`#Upp`:`:GraphDraw`_ns`:`:TickMark`:`:class^@(0.0.255) T
ickMark][@(0.0.255) `&]_[* GetTickMark]()_[@(0.0.255) const]&]
[s5;:Upp`:`:GraphDraw`_ns`:`:MarkerElementData`:`:operator TickMark`&`(`)const: [* oper
ator_TickMark`&]()_[@(0.0.255) const]&]
[s2;%% Returns tickmark instance used to draw the marker&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:MarkerElementData`:`:GetPos`(`)const: [_^TypeGraphCoord^ T
ypeGraphCoord]_[* GetPos]()_[@(0.0.255) const]&]
[s2; Returns the marker position&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:MarkerElementData`:`:operator TypeGraphCoord`(`)const: [* o
perator_TypeGraphCoord]()_[@(0.0.255) const]&]
[s2;%% Returns marker position value&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:MarkerElementData`:`:operator`=`(const TypeGraphCoord`): [_^MarkerElementData^ M
arkerElementData][@(0.0.255) `&]_[* operator`=]([@(0.0.255) const]_[_^TypeGraphCoord^ Typ
eGraphCoord]_[*@3 v])&]
[s5;:Upp`:`:GraphDraw`_ns`:`:MarkerElementData`:`:operator`=`(const MarkerElementData`): [_^Upp`:`:GraphDraw`_ns`:`:MarkerElementData^ M
arkerElementData][@(0.0.255) `&]_[* operator`=](_[@(0.0.255) const]_[_^Upp`:`:GraphDraw`_ns`:`:MarkerElementData^ M
arkerElementData]_[*@3 v]_)&]
[s5;:Upp`:`:GraphDraw`_ns`:`:MarkerElementData`:`:operator`=`(const MarkerElementData`*`): [_^Upp`:`:GraphDraw`_ns`:`:MarkerElementData^ M
arkerElementData][@(0.0.255) `&]_[* operator`=](_[@(0.0.255) const]_[_^Upp`:`:GraphDraw`_ns`:`:MarkerElementData^ M
arkerElementData][@(0.0.255) `*]_[*@3 v]_)&]
[s5;:Upp`:`:GraphDraw`_ns`:`:MarkerElementData`:`:SetPos`(TypeGraphCoord`): [@(0.0.255) v
oid]_[* SetPos]([_^Upp`:`:GraphDraw`_ns`:`:TypeGraphCoord^ TypeGraphCoord]_[*@3 v])&]
[s2; [%% Set the marker position value to ][*@3 v]&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:MarkerElementData`:`:GetID`(`)const: [@(0.0.255) int]_[* Get
ID]()_[@(0.0.255) const]&]
[s2;%% Returns marker ID  or  [*@3 INVALID`_MARKER`_ID ]if invalid&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:MarkerElementData`:`:CreateMarker`(int`,void`*`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 T]>_[*@4 T][@(0.0.255) `&]_[* CreateMarker]([@(0.0.255) uns
igned]_[@(0.0.255) int]_[*@3 id], [@(0.0.255) void`*]_[*@3 own])&]
[s2;%%  [%-*@3 id] [%-*@3 own] .&]
[s2;%% Method used to create the TickMark instance used by the marker.&]
[s2;%%  [%-*@4 T] : TickMark class to use ( a new instance is created 
)&]
[s2;%%  [%-*@3 id] : marker id set   (negative values are not allowed)&]
[s3;%% &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 MarkerPosList type]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:MarkerPosList: [@(0.0.255) typedef]_[_^ArrayMap^ ArrayMap]<[@(0.0.255) i
nt], [_^MarkerElementData^ MarkerElementData]>_[* MarkerPosList]&]
[s2;%% Container of MarkerElementData instances&]
[s3; &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 MarkerElement class]]}}&]
[s4; &]
[s1;:noref: [@(0.0.255)3 template][3 _<][@(0.0.255)3 class][3 _][*@4;3 TYPES][3 >]&]
[s1;:Upp`:`:GraphDraw`_ns`:`:MarkerElement`:`:class: [@(0.0.255) class]_[* MarkerElement]_
:_[@(0.0.255) public]_[*@3 GraphElement]&]
[s2;%% &]
[s3; &]
[s0;i448;a25;kKO9;@(0.0.255) &]
[ {{10000F(128)G(128)@1 [s0;%% [* Function List]]}}&]
[s0;i448;a25;kKO9;:noref:@(0.0.255) &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Method List]]}}&]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor detail]]}}&]
[s0;%% &]
[s0;%% ]]