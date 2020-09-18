import Project from require "ice.workspace.project"

with Project "IceCodeEmitter"
    \script 'ice.bat'
    \fastbuild_script 'source/fbuild.bff'
    \fastbuild_vstudio_solution 'CodeEmitter'

    \sources 'source/code'
    \output 'build'
    \working_dir 'build'
    \finish!
