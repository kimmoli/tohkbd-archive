<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.4">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="pogopins">
<packages>
<package name="POGOPINS">
<smd name="INT" x="-8" y="0" dx="1.5" dy="2" layer="1" roundness="100"/>
<smd name="V33" x="-5.5" y="0" dx="1.5" dy="2" layer="1" roundness="100"/>
<smd name="SDA" x="3" y="0" dx="1.5" dy="2" layer="1" roundness="100"/>
<smd name="SCL" x="7.5" y="0" dx="1.5" dy="2" layer="1" roundness="100"/>
<text x="-5.1" y="-5.05" size="1.27" layer="25" font="vector">Pogo Pins</text>
<text x="-9.9" y="-2.8" size="1.27" layer="21" font="vector">INT</text>
<text x="-6" y="-2.8" size="1.27" layer="21" font="vector">V33</text>
<text x="1.4" y="-2.8" size="1.27" layer="21" font="vector">SDA</text>
<text x="5.9" y="-2.8" size="1.27" layer="21" font="vector">SCL</text>
<smd name="GND" x="13" y="43" dx="1.5" dy="2" layer="1" roundness="100" rot="R90"/>
<text x="12.7" y="44.45" size="1.27" layer="21">GND</text>
</package>
</packages>
<symbols>
<symbol name="POGOPINS">
<wire x1="-7.62" y1="0" x2="12.7" y2="0" width="0.254" layer="94"/>
<pin name="INT" x="-7.62" y="5.08" length="middle" rot="R270"/>
<pin name="V33" x="-2.54" y="5.08" length="middle" rot="R270"/>
<pin name="SDA" x="2.54" y="5.08" length="middle" rot="R270"/>
<pin name="SCL" x="7.62" y="5.08" length="middle" rot="R270"/>
<pin name="GND" x="12.7" y="5.08" length="middle" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="POGOPINS" prefix="POGO-">
<gates>
<gate name="G$1" symbol="POGOPINS" x="0" y="0"/>
</gates>
<devices>
<device name="" package="POGOPINS">
<connects>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="INT" pad="INT"/>
<connect gate="G$1" pin="SCL" pad="SCL"/>
<connect gate="G$1" pin="SDA" pad="SDA"/>
<connect gate="G$1" pin="V33" pad="V33"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="6Pconnector">
<packages>
<package name="6PCONNECTOR">
<smd name="PIN3" x="-0.25" y="0.35" dx="0.3" dy="0.7" layer="1" rot="R180"/>
<smd name="PIN4" x="0.25" y="0.35" dx="0.3" dy="0.7" layer="1" rot="R180"/>
<smd name="PIN5" x="0.75" y="0.35" dx="0.3" dy="0.7" layer="1" rot="R180"/>
<smd name="PIN6" x="1.25" y="0.35" dx="0.3" dy="0.7" layer="1" rot="R180"/>
<smd name="PIN2" x="-0.75" y="0.35" dx="0.3" dy="0.7" layer="1" rot="R180"/>
<smd name="PIN1" x="-1.25" y="0.35" dx="0.3" dy="0.7" layer="1" rot="R180"/>
<smd name="GND2" x="2.05" y="-2.3" dx="0.3" dy="1" layer="1" rot="R180"/>
<smd name="GND1" x="-2.05" y="-2.3" dx="0.3" dy="1" layer="1" rot="R180"/>
</package>
</packages>
<symbols>
<symbol name="6PCONNECTOR">
<pin name="PIN1" x="-10.16" y="5.08" length="middle" rot="R270"/>
<pin name="PIN2" x="-5.08" y="5.08" length="middle" rot="R270"/>
<pin name="PIN3" x="0" y="5.08" length="middle" rot="R270"/>
<pin name="PIN4" x="5.08" y="5.08" length="middle" rot="R270"/>
<pin name="PIN5" x="10.16" y="5.08" length="middle" rot="R270"/>
<pin name="PIN6" x="15.24" y="5.08" length="middle" rot="R270"/>
<wire x1="-10.16" y1="0" x2="15.24" y2="0" width="0.254" layer="94"/>
<pin name="GND2" x="20.32" y="0" length="middle" rot="R180"/>
<pin name="GND1" x="-15.24" y="0" length="middle"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="6PCONNECTOR">
<gates>
<gate name="G$1" symbol="6PCONNECTOR" x="-2.54" y="0"/>
</gates>
<devices>
<device name="" package="6PCONNECTOR">
<connects>
<connect gate="G$1" pin="GND1" pad="GND1"/>
<connect gate="G$1" pin="GND2" pad="GND2"/>
<connect gate="G$1" pin="PIN1" pad="PIN1"/>
<connect gate="G$1" pin="PIN2" pad="PIN2"/>
<connect gate="G$1" pin="PIN3" pad="PIN3"/>
<connect gate="G$1" pin="PIN4" pad="PIN4"/>
<connect gate="G$1" pin="PIN5" pad="PIN5"/>
<connect gate="G$1" pin="PIN6" pad="PIN6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="POGO-1" library="pogopins" deviceset="POGOPINS" device=""/>
<part name="U$1" library="6Pconnector" deviceset="6PCONNECTOR" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="POGO-1" gate="G$1" x="58.42" y="73.66"/>
<instance part="U$1" gate="G$1" x="55.88" y="111.76"/>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="POGO-1" gate="G$1" pin="GND"/>
<wire x1="71.12" y1="78.74" x2="71.12" y2="81.28" width="0.1524" layer="91"/>
<label x="71.12" y="83.82" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="PIN2"/>
<wire x1="50.8" y1="116.84" x2="50.8" y2="119.38" width="0.1524" layer="91"/>
<label x="50.8" y="119.38" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="PIN4"/>
<wire x1="60.96" y1="116.84" x2="60.96" y2="119.38" width="0.1524" layer="91"/>
<label x="60.96" y="119.38" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="V33" class="0">
<segment>
<pinref part="POGO-1" gate="G$1" pin="V33"/>
<wire x1="55.88" y1="78.74" x2="55.88" y2="81.28" width="0.1524" layer="91"/>
<label x="55.88" y="83.82" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="PIN1"/>
<wire x1="45.72" y1="116.84" x2="45.72" y2="119.38" width="0.1524" layer="91"/>
<label x="45.72" y="119.38" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="INT" class="0">
<segment>
<pinref part="POGO-1" gate="G$1" pin="INT"/>
<wire x1="50.8" y1="78.74" x2="50.8" y2="81.28" width="0.1524" layer="91"/>
<label x="50.8" y="83.82" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="PIN6"/>
<wire x1="71.12" y1="116.84" x2="71.12" y2="119.38" width="0.1524" layer="91"/>
<label x="71.12" y="119.38" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="SCL" class="0">
<segment>
<pinref part="POGO-1" gate="G$1" pin="SCL"/>
<wire x1="66.04" y1="78.74" x2="66.04" y2="81.28" width="0.1524" layer="91"/>
<label x="66.04" y="83.82" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="PIN3"/>
<wire x1="55.88" y1="116.84" x2="55.88" y2="119.38" width="0.1524" layer="91"/>
<label x="55.88" y="119.38" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="SDA" class="0">
<segment>
<pinref part="POGO-1" gate="G$1" pin="SDA"/>
<wire x1="60.96" y1="78.74" x2="60.96" y2="81.28" width="0.1524" layer="91"/>
<label x="60.96" y="83.82" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="PIN5"/>
<wire x1="66.04" y1="116.84" x2="66.04" y2="119.38" width="0.1524" layer="91"/>
<label x="66.04" y="119.38" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
