topic "Properties Dialog management";
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
[ {{10000@(113.42.0) [s0; [*@7;4 GEPropertiesDlgInterface]]}}&]
[s1;:Upp`:`:GraphDraw`_ns`:`:GEPropertiesDlgInterface`:`:class: [@(0.0.255)3 class][3 _][*3 G
EPropertiesDlgInterface][3 _:_][@(0.0.255)3 public][3 _][*@3;3 ParentCtrl]&]
[s2;%% Base class for all GraphElement Properties dialog classes.&]
[s2;%% This is mainly to ensure that the Retreive() method is available.&]
[s3; &]
[s0;@(0.0.255) &]
[ {{10000@(113.42.0) [s0; [*@7;4 MultiGEPropertiesDlg]]}}&]
[s0;@(0.0.255) &]
[s1;:noref: [@(0.0.255)3 template][3 _<][@(0.0.255)3 class][3 _][*@3;3 BASE][3 >]&]
[s1;:Upp`:`:GraphDraw`_ns`:`:MultiGEPropertiesDlg`:`:class: [@(0.0.255) class]_[* MultiGE
PropertiesDlg]_:_[@(0.0.255) public]_[*@3 BASE]&]
[s2; [%% Utility dialog class that enables displaying in one dialog 
multiple GraphElement properties dialogs. It is therefor a container 
for GraphElement properties dialogs so it ]manages a list of 
[^topic`:`/`/GraphCtrl`/src`/PropertiesDialog`_en`-us`#Upp`:`:GraphDraw`_ns`:`:GEPropertiesDlgInterface`:`:class^ G
EPropertiesDlgInterface.]&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:MultiGEPropertiesDlg`:`:elemPropDlgList: [^topic`:`/`/GraphCtrl`/src`/PropertiesDialog`_en`-us`#Upp`:`:GraphDraw`_ns`:`:GEPropertiesDlgInterface`:`:class^ G
EPropertiesDlgInterface][_^Upp`:`:GraphDraw`_ns`:`:GEPropertiesDlgInterface`:`:VList^ `:
:VList]_[* elemPropDlgList]&]
[s2; [%% List of all contained ]GEPropertiesDlgInterface instances&]
[s2; All contained instances are owned : so they will be deleted in 
destructor.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:MultiGEPropertiesDlg`:`:AddSubElement`(int`,int`&`,ELEMENT`&`,ESTYLE`&`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 ELEMENT], [@(0.0.255) class]_[*@4 ESTYLE]>_[@(0.0.255) vo
id]_[* AddSubElement]([@(0.0.255) int]_[*@3 sepDist], [@(0.0.255) int`&]_[*@3 yOffset], 
[*@4 ELEMENT][@(0.0.255) `&]_[*@3 ELEM`_], [*@4 ESTYLE][@(0.0.255) `&]_[*@3 STYL`_])&]
[s2;%% [%-*@3 sepDist] : vertical separation distance from previous 
dialog in current tab&]
[s2;%% [%-*@3 yOffset] : input/output param: it is used to know where 
the next dialog should start.&]
[s2;%% Add a graph element properties dialog to the container positionning 
and layout being managed.&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:MultiGEPropertiesDlg`:`:AddSubCElement`(int`,int`&`,ELEMENT`&`,int`): [@(0.0.255) t
emplate] <[@(0.0.255) class] ELEMENT> [@(0.0.255) void] [* AddSubCElement]([@(0.0.255) in
t] [*@3 sepDist], [@(0.0.255) int`&] [*@3 yOffset], ELEMENT[@(0.0.255) `&] 
[*@3 ELEM`_], [@(0.0.255) int] [*@3 sepHeight] [@(0.0.255) `=] [@3 0])&]
[s2;%%  [%-*@3 sepDist] [%-*@3 yOffset] [%-*@3 ELEM`_] [%-*@3 sepHeight] 
.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:MultiGEPropertiesDlg`:`:Retrieve`(`): [@(0.0.255) virtual] 
[@(0.0.255) void]_[* Retrieve]()&]
[s2; [%% Launches Retreive on all the contained ]GEPropertiesDlgInterface&]
[s3; &]
[s0;@(0.0.255) &]
[ {{10000@(113.42.0) [s0; [*@7;4 PropertiesTabBase]]}}&]
[s3; &]
[s1;:Upp`:`:GraphDraw`_ns`:`:PropertiesTabBase`:`:class: [@(0.0.255)3 class][3 _][*3 Proper
tiesTabBase][3 _:_][@(0.0.255)3 public][3 _][*@3;3 WithElementDlgLayout][3 <][_^Upp`:`:GraphDraw`_ns`:`:GEPropertiesDlgInterface^3 E
lementPropertiesDlgInterface][3 >_]&]
[s2;%% Base class of Ctrl that are put on tabs of the Graph properties 
editor dialog.&]
[s2; [%% There is one ]PropertiesTabBase per tab.&]
[s3;%% &]
[s0;*@7;4%% &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 Title]]}}&]
[s0;i448;a25;kKO9;@(0.0.255) &]
[ {{10000F(128)G(128)@1 [s0;%% [* Function List]]}}&]
[s0;i448;a25;kKO9;:noref:@(0.0.255) &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Method List]]}}&]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor detail]]}}&]
[s0;%% ]]