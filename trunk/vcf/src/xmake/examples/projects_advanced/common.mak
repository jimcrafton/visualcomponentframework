<config name="GCC Debug">
	<!-- un-comment this out if you want to add
	custom include paths for this configuration.
		<include path=""/>
	-->

	<!-- compiler tool -->
	<tool id="cc" name="g++" type=".cc;.cpp;.cxx">
		<flags value="-o $(dependency.output) -g -I ./ -D _DEBUG -c "/>
		<exec command="g++ -o $(dependency.output) -g -I ./ -D _DEBUG -c  $(dependency.name) "/>
	</tool>

	<!-- linker tool -->
	<tool id="link" name="g++" >
		<flags value="-o "/>
		<exec command="g++ -o  $(target.output) $(dependsOn.children.output) "/>
	</tool>
</config>

<variable name="obj_ext" value="o"/>
