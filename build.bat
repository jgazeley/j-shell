# Run these commands from your project root (D:\Desktop\cli>)

# 1. Ensure the build directory exists
New-Item -ItemType Directory -Force -Path 'build'

# 2. Compile your project
cl /nologo /Od /Zi /EHsc /I include /D ENABLE_CLI=1 /D PLATFORM_HOST=1 /Fobuild\ /Febuild\cli_host.exe src\main.c src\core.c src\menu.c src\menu_definitions.c src\command.c src\plugins.c src\plugin_test.c src\io_host.c src\utils\format.c