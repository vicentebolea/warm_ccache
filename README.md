# WARM_CCACHE

Utility to populate ccache with the latest master of a git based project.

It will recompile the project with the latest branch once a day.

## install

Add your configuration to the `config.c` file.

```
  cmake .  # You could add -DWARM_CCACHE_WHEN=*-*-* 10:10:10
  sudo make install

  # Enable systemd timer
  systemctl --user enable warm_ccache.service
  systemctl --user enable warm_ccache.timer
  systemctl --user start warm_ccache.timer
```

You can check the logs later with `journalctl -u warm_ccache`.

## Authors
 - Vicente Adolfo Bolea Sanchez <vicente.bolea@gmail.com>
