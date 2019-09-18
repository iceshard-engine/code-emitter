import Application from require "ice.application"

class Ice extends Application
    @name: 'Ice - Code Emitter'
    @description: 'A specific tool for parsing and emitting code'
    @arguments: { }

    -- Plain call to the application
    execute: (args) =>
        print 'Ice (CodeEmitter) - v0.0.1'
        print ''
        print '> For more options see the -h,--help output.'

Ice!\run!
