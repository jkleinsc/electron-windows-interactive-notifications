{
  "targets": [
    {
      "target_name": "notifications_bindings",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "xcode_settings": { "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
        "CLANG_CXX_LIBRARY": "libc++",
        "MACOSX_DEPLOYMENT_TARGET": "10.7",
      },
      "msvs_settings": {
        "VCCLCompilerTool": { "ExceptionHandling": 1 },
      },
      "sources": [
	    "lib/notifications_bindings.cc"
	  ],
	  "libraries": [ "-lruntimeobject.lib","-lshlwapi.lib" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
				"./InteractiveNotifications"
      ],
	  "link_settings": {
		"libraries": [
			"-lInteractiveNotifications.lib",
		]
	  },
	  "configurations": {
			"Debug": {
				"conditions": [
					['target_arch=="x64"', {
						"msvs_settings": {
							"VCLinkerTool": {
								"AdditionalLibraryDirectories": [
									"../x64/Release"
								],
							}
						}
					}],
					['target_arch=="ia32"', {
						"msvs_settings": {
							"VCLinkerTool": {
								"AdditionalLibraryDirectories": [
									"../Release"
								],
							}
						}
					}]
				]
			},
			"Release": {
				"conditions": [
					['target_arch=="x64"', {
						"msvs_settings": {
							"VCLinkerTool": {
								"AdditionalLibraryDirectories": [
									"../x64/Release"
								],
							}
						}
					}],
					['target_arch=="ia32"', {
						"msvs_settings": {
							"VCLinkerTool": {
								"AdditionalLibraryDirectories": [
									"../Release"
								],
							}
						}
					}]
				]
			},
	  }
	}
  ]
}