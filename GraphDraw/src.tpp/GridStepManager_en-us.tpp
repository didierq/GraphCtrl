topic "9 - Grid Step management";
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
[s0; &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 GridStepData Class]]}}&]
[s1;:Upp`:`:GraphDraw`_ns`:`:GridStepData`:`:class: [@(0.0.255)3 class][3 _][*3 GridStepDat
a]&]
[s2;%% Container for grid step data.&]
[s2;%% Contains all the data useful for rendering a grid step (even 
custom data)&]
[s2;%% See [^topic`:`/`/GraphDraw`/srcdoc`/2`_GridManagement`$en`-us`#Grid Management^ G
rid Management] for more details.&]
[s3; &]
[s0; &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 GridStepIterator Class]]}}&]
[s1;:Upp`:`:GraphDraw`_ns`:`:GridStepIterator`:`:class: [@(0.0.255)3 class][3 _][*3 GridSte
pIterator]&]
[s2;%% [^topic`:`/`/GraphDraw`/src`/GridStepIterator`$en`-us`#Upp`:`:GraphDraw`_ns`:`:GridStepIterator`:`:class^ G
ridStepIterator] class is a container for the precalculated grid 
step values which will be used by the drawing methods.&]
[s2;%% See [^topic`:`/`/GraphDraw`/srcdoc`/2`_GridManagement`$en`-us`#Grid Management^ G
rid Management] for more details.&]
[s3; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Method List]]}}&]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor detail]]}}&]
[s4; &]
[s0;*@7;4%% &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 FormatText CallBack]]}}&]
[s0;@(0.0.255) &]
[s0; [@(0.0.255) typedef]_[_^Upp`:`:Callback2^ Callback2]<_[@(0.0.255) const]_GridStepItera
tor[@(0.0.255) `&], String[@(0.0.255) `&]>_[* TypeFormatTextCbk]&]
[s2;%% CallBack that define interface for converting current grid 
step value into formated text.&]
[s3; &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 GridStepManager Class]]}}&]
[s0; &]
[s1;:Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:class: [@(0.0.255)3 class][3 _][*3 GridStep
Manager]&]
[s2;%% This class is used to manage grids steps :[*@3 How many `&where] 
the steps are to be positionned, [*@6 NOT ][*@3 how they are drawn 
!]&]
[s2;%% It uses a reference to the corresponding [^topic`:`/`/GraphDraw`/src`/CoordinateConverter`$en`-us`#Upp`:`:GraphDraw`_ns`:`:CoordinateConverter`:`:class^ C
oordinateConverter ]instance to calculate step values and position 
them correctly in the [^topic`:`/`/GraphDraw`/srcdoc`/1`_GraphDraw`_basics`$en`-us`#Plot Areas definition^ P
lotArea].&]
[s2;%% Whith this class you can manage any sort of grid.&]
[s2;%% The current existing types are :&]
[s2;i150;O0;%% [* Standard]&]
[s2;i150;O0;%% [* Log10]&]
[s2;i150;O0;%% [* Date  ]: Grid step value is Upp`::Date&]
[s2;i150;O0;%% [* Time  ]: Grid step value is Upp`::Time&]
[s2;i150;O0;%% [* Custom]&]
[s2;%% &]
[s2;%% Custom grid step management is enabled through the use of 
a callback intended to caculate the values : see &]
[s2;%% &]
[s2;%% Grid steps wallthrough is brought by the [^topic`:`/`/GraphDraw`/src`/GridStepIterator`$en`-us`#Upp`:`:GraphDraw`_ns`:`:GridStepIterator`:`:class^ G
ridStepIterator] class which is a container for the precalculated 
grid step values, and which the will be used by the drawing methods&]
[s2;%% &]
[s2;%% See [^topic`:`/`/GraphDraw`/srcdoc`/2`_GridManagement`$en`-us`#Grid Management^ G
rid Management] for more details.&]
[s3; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Method List]]}}&]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:`_nbMaxSteps: [@(0.0.255) unsigned]_[@(0.0.255) i
nt]_[* `_nbMaxSteps]&]
[s2;%% Maximum culculated number of steps taking into account mean 
text size text for the current grid.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:GetNormalizedStep`(Upp`:`:GraphDraw`_ns`:`:TypeGraphCoord`,unsigned int`): [_^Upp`:`:GraphDraw`_ns`:`:TypeGraphCoord^ T
ypeGraphCoord]_[* GetNormalizedStep]([_^Upp`:`:GraphDraw`_ns`:`:TypeGraphCoord^ TypeG
raphCoord]_[*@3 range], [@(0.0.255) unsigned]_[@(0.0.255) int]_[*@3 nbMaxSteps])&]
[s2;%% Returns the step value between two grid steps.&]
[s2;%% The step value is normalized to be `{2, 5, 10`}`*10`^n.&]
[s2;%% [%-*@3 range] : graph range&]
[s2;%% [%-*@3 nbMaxSteps] : max nbr of steps allowed&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:GetNormalizedStep`(Upp`:`:GraphDraw`_ns`:`:TypeGraphCoord`,const Upp`:`:Vector`<T`>`&`,unsigned int`): [@(0.0.255) s
tatic] [@(0.0.255) template]_<[@(0.0.255) class]_[*@4 T]>_[*@4 T]_[* GetNormalizedStep]([_^Upp`:`:GraphDraw`_ns`:`:TypeGraphCoord^ T
ypeGraphCoord]_[*@3 range], [@(0.0.255) const]_[_^Upp`:`:Vector^ Vector]<[*@4 T]>`&_[*@3 st
epValues], [@(0.0.255) unsigned]_[@(0.0.255) int]_[*@3 nbMaxSteps])&]
[s2;%% Returns the step value between two grid steps..&]
[s2; [%% The step value is normalized according to the values contained 
in ][*@3 stepValues]&]
[s2;%% [%-*@3 range] : graph range&]
[s2;%% [%-*@3 nbMaxSteps] : max nbr of steps allowed&]
[s2;%% [%-*@3 stepValues] : list of values the step can take &]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:setCustomGridSteps`(Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:TypeGridStepCalcCallBack`): [@(0.0.255) v
oid]_[* setCustomGridSteps]([_^Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:TypeGridStepCalcCallBack^ T
ypeGridStepCalcCallBack]_[*@3 cbk])&]
[s2;%% Set callback [%-*@3 cbk] that will be used to calculate grid 
steps.&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:GetGridStartValue`(Upp`:`:GraphDraw`_ns`:`:TypeGraphCoord`,Upp`:`:GraphDraw`_ns`:`:TypeGraphCoord`): [@(0.0.255) s
tatic] [_^Upp`:`:GraphDraw`_ns`:`:TypeGraphCoord^ TypeGraphCoord]_[* GetGridStartValu
e]([_^Upp`:`:GraphDraw`_ns`:`:TypeGraphCoord^ TypeGraphCoord]_[*@3 stepValue], 
[_^Upp`:`:GraphDraw`_ns`:`:TypeGraphCoord^ TypeGraphCoord]_[*@3 graphMin])&]
[s2;%% Calculates the value of the first grid taking into account 
the [%-*@3 stepValue] and [%-*@3 graphMin].&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:setStdGridSteps`(`): [@(0.0.255) void]_
[* setStdGridSteps]()&]
[s2;%% &]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:setLogGridSteps`(`): [@(0.0.255) void]_
[* setLogGridSteps]()&]
[s2;%% &]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:setTimeGridSteps`(`): [@(0.0.255) void]_
[* setTimeGridSteps]()&]
[s2;%% &]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:setDateGridSteps`(`): [@(0.0.255) void]_
[* setDateGridSteps]()&]
[s2;%% &]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:UpdateGridSteps`(const int`): [@(0.0.255) v
irtual] [@(0.0.255) void]_[* UpdateGridSteps]([@(0.0.255) const]_[@(0.0.255) int]_[*@3 scal
e]_`=_[@3 1])&]
[s2;%%  [%-*@3 scale] .&]
[s3;%% &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:GetNbSteps`(`)const: [@(0.0.255) unsign
ed int]_[* GetNbSteps]()_[@(0.0.255) const]&]
[s2;%% Returns current number of steps available in current graph 
range&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:GetNbMaxSteps`(`)const: [@(0.0.255) uns
igned int]_[* GetNbMaxSteps]()_[@(0.0.255) const]&]
[s2;%% Returns MAX number of steps that allow a good looking grid 
and prevents a to tight grid.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:SetTextMaxSize`(double`): [@(0.0.255) b
ool]_[* SetTextMaxSize]([@(0.0.255) double]_[*@3 textSize])&]
[s2;%% Set the maximum size of the text for the current grid step 
values.&]
[s2;%% Note: this value is calculated from the grid step text values&]
[s3;%% &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Grid Steps Iterator]]}}&]
[s4;* &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:End`(`): [_^Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:Iterator^ I
terator]_[* End]()&]
[s2;%% Returns End Iterator (instance of [^topic`:`/`/GraphDraw`/src`/GridStepIterator`$en`-us`#Upp`:`:GraphDraw`_ns`:`:GridStepIterator`:`:class^ G
ridStepIterator])&]
[s3; &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:Begin`(`): [_^Upp`:`:GraphDraw`_ns`:`:GridStepManager`:`:Iterator^ I
terator]_[* Begin]()&]
[s2;%% Returns Begin Iterator : Points on first step of grid (instance 
of [^topic`:`/`/GraphDraw`/src`/GridStepIterator`$en`-us`#Upp`:`:GraphDraw`_ns`:`:GridStepIterator`:`:class^ G
ridStepIterator])&]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor detail]]}}&]
[s3; &]
[s0;%% ]]