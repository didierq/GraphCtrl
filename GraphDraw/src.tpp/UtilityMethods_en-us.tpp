topic "9 - Utility Methods";
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
[{_}%EN-US 
[s0;*@7;4 &]
[ {{10000@(113.42.0) [s0; [*@7;4 Title]]}}&]
[s0;i448;a25;kKO9;@(0.0.255)%- &]
[ {{10000F(128)G(128)@1 [s0; [* Public Function List]]}}&]
[s4;%- &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GetSmartTextHeight`(const char`*`,int`,const Font`,int`):%- [@(0.0.255) i
nt] [* GetSmartTextHeight]([@(0.0.255) const] [@(0.0.255) char] [@(0.0.255) `*][*@3 s], 
[@(0.0.255) int] [*@3 cx], [@(0.0.255) const] Font [*@3 font], [@(0.0.255) int] 
[*@3 scale] [@(0.0.255) `=] [@3 1])&]
[s2;  [%-*@3 s] [%-*@3 cx] [%-*@3 font] [%-*@3 scale] .&]
[s3;%- &]
[s4;%- &]
[s5;:Upp`:`:GraphDraw`_ns`:`:DrawSmartText`(Draw`&`,int`,int`,int`,const char`*`,const Font`,Color`,int`):%- [@(0.0.255) v
oid]_[* DrawSmartText]([_^Upp`:`:Draw^ Draw][@(0.0.255) `&]_[*@3 draw], 
[@(0.0.255) int]_[*@3 x], [@(0.0.255) int]_[*@3 y], [@(0.0.255) int]_[*@3 cx], 
[@(0.0.255) const]_[@(0.0.255) char]_`*[*@3 text], [@(0.0.255) const]_[_^Upp`:`:Font^ Font]_
[*@3 scaledFont], [_^Upp`:`:Color^ Color]_[*@3 ink], [@(0.0.255) int]_[*@3 scale])&]
[s2;  [%-*@3 draw] [%-*@3 x] [%-*@3 y] [%-*@3 cx] [%-*@3 text] [%-*@3 scaledFont] 
[%-*@3 ink] [%-*@3 scale] .&]
[s3; &]
[s4;%- &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GetSmartTextSize`(const char`*`,const Font`,int`,int`):%- S
ize [* GetSmartTextSize]([@(0.0.255) const] [@(0.0.255) char] [@(0.0.255) `*][*@3 text], 
[@(0.0.255) const] Font [*@3 scaledFont], [@(0.0.255) int] [*@3 scale] 
[@(0.0.255) `=] [@3 1], [@(0.0.255) int] [*@3 cx] [@(0.0.255) `=] [@3 2147483647])&]
[s2;  [%-*@3 text] [%-*@3 scaledFont] [%-*@3 scale] [%-*@3 cx] .&]
[s3;%- &]
[s4; &]
[s5;:Upp`:`:GraphDraw`_ns`:`:GetElementSubArea`(PointScreen`,RectScreen`,int`):%- Ele
mentBorderPosition_[* GetElementSubArea](_[_^Upp`:`:GraphDraw`_ns`:`:PointScreen^ Poi
ntScreen]_[*@3 p], [_^Upp`:`:GraphDraw`_ns`:`:RectScreen^ RectScreen]_[*@3 r], 
[@(0.0.255) int]_[*@3 borderWidth]_)&]
[s2; [%-*@3 p] :&]
[s2; [%-*@3 r] :&]
[s2; [%-*@3 borderWidth] :&]
[s2; Utility function that returns the part of `'r`' in which `'p`' 
is positioned : TOP, BOTTOM, CORNER, .....&]
[s3; &]
[s0;i448;a25;kKO9;:noref:@(0.0.255)%- &]
[ {{10000F(128)G(128)@1 [s0; [* Public Method List]]}}&]
[s0; ]]