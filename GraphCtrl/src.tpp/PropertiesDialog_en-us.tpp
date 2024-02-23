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
[ {{10000@(113.42.0) [s0; [*@7;4 ElementPropertiesDlgInterface]]}}&]
[s1;:Upp`:`:GraphDraw`_ns`:`:ElementPropertiesDlgInterface`:`:class: [@(0.0.255)3 class
][3 _][*3 ElementPropertiesDlgInterface][3 _:_][@(0.0.255)3 public][3 _][*@3;3 ParentCtrl]&]
[s2;%% Base class for all GraphElement Properties dialog classes.&]
[s2;%% This is mainly to ensure that the Retreive() method is available.&]
[s3; &]
[s0;*@7;4%% &]
[ {{10000@(113.42.0) [s0; [*@7;4 ElementPropertiesDlgInfo]]}}&]
[s1;:Upp`:`:GraphDraw`_ns`:`:ElementPropertiesDlgInfo`:`:class: [@(0.0.255)3 class][3 _][*3 E
lementPropertiesDlgInfo]&]
[s2;%% Class that serves as a container for a GraphElement properties 
dialog info.&]
[s2;%% It contains the dialog instance (initialized with the styling 
information) and several Function that help manage/use the dialog:&]
[s2;l416;i150;O0; [* DeleteDlg]&]
[s2;l416;i150;O0; [* RetrieveFromDlg]&]
[s2;l416;i150;O0; [* WhenDlgAction]&]
[s2;%% This class is needed to enable clean GraphDraw / GraphCtrl 
separation&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:ElementPropertiesDlgInfo`:`:DeleteDlg: [_^Upp`:`:Function^ F
unction]<[@(0.0.255) void]()>_[* DeleteDlg]&]
[s2;%% Destroys the dialog instance&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:ElementPropertiesDlgInfo`:`:RetrieveFromDlg: [_^Upp`:`:Function^ F
unction]<[@(0.0.255) void]()>_[* RetrieveFromDlg]&]
[s2;%% Retreives data from the dialog and sets the style with the 
values in dialog (This will apply changes to the style)&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:ElementPropertiesDlgInfo`:`:WhenDlgAction: [_^Upp`:`:Function^ F
unction]<[@(0.0.255) void]()>_[* WhenDlgAction]&]
[s2;%% Called when an action is done in the dialog editor.&]
[s3; &]
[s0;@(0.0.255) &]
[ {{10000@(113.42.0) [s0; [*@7;4 ElementPropertiesContainer]]}}&]
[s0;@(0.0.255) &]
[s1;:noref: [@(0.0.255)3 template][3 _<][@(0.0.255)3 class][3 _][*@3;3 BASE][3 >]&]
[s1;:Upp`:`:GraphDraw`_ns`:`:ElementPropertiesContainer`:`:class: [@(0.0.255) class]_[* E
lementPropertiesContainer]_:_[@(0.0.255) public]_[*@3 BASE]&]
[s2;%% Layering class that adds container capacities.&]
[s2; It allows managing a list of [^topic`:`/`/GraphCtrl`/src`/PropertiesDialog`_en`-us`#Upp`:`:GraphDraw`_ns`:`:ElementPropertiesDlgInterface`:`:class^ E
lementPropertiesDlgInterface]&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:ElementPropertiesContainer`:`:elemPropDlgList: [_^Upp`:`:GraphDraw`_ns`:`:ElementPropertiesDlgInterface`:`:VList^ E
lementPropertiesDlgInterface`::VList]_[* elemPropDlgList]&]
[s2; [%% List of all contained ]ElementPropertiesDlgInterface instances&]
[s2; All contained instances are owned : so they will be deleted.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:ElementPropertiesContainer`:`:AddSubElement`(int`,int`&`,ELEMENT`&`,ESTYLE`&`): [@(0.0.255) t
emplate]_<[@(0.0.255) class]_[*@4 ELEMENT], [@(0.0.255) class]_[*@4 ESTYLE]>_[@(0.0.255) vo
id]_[* AddSubElement]([@(0.0.255) int]_[*@3 sepWidth], [@(0.0.255) int`&]_[*@3 yOffset], 
[*@4 ELEMENT][@(0.0.255) `&]_[*@3 ELEM`_], [*@4 ESTYLE][@(0.0.255) `&]_[*@3 STYL`_])&]
[s2;%% [%-*@3 sepWidth] : vertical separation width from previous dialog 
contribution in current tab&]
[s2;%% [%-*@3 yOffset] : must contain [%-*@3 ELEM`_] [%-*@3 STYL`_] .&]
[s2;%% Add a graph element properties dialog to the container positionning 
and layout being managed.&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:ElementPropertiesContainer`:`:Retrieve`(`): [@(0.0.255) vi
rtual] [@(0.0.255) void]_[* Retrieve]()&]
[s2; [%% Launches Retreive on all the contained ]ElementPropertiesDlgInterface&]
[s3; &]
[s0;@(0.0.255) &]
[ {{10000@(113.42.0) [s0; [*@7;4 PropertiesTabBase]]}}&]
[s3; &]
[s1;:Upp`:`:GraphDraw`_ns`:`:PropertiesTabBase`:`:class: [@(0.0.255)3 class][3 _][*3 Proper
tiesTabBase][3 _:_][@(0.0.255)3 public][3 _][*@3;3 WithElementDlgLayout][3 <][_^Upp`:`:GraphDraw`_ns`:`:ElementPropertiesDlgInterface^3 E
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