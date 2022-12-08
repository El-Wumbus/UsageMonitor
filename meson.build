project('uum', 'c')

cc = meson.get_compiler('c')

curses = cc.find_library('curses', required: true)

executable(
  'uum',
  'src/main.c',
  'src/info.c',
  'src/collect.c',
  dependencies: curses
)
