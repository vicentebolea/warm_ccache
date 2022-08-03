# KW-CCACHE

Utility to populate ccache with the latest master of a git based project.

It will recompile the project with the latest branch once a day.

## install

Add your configuration to the `~/.kw-ccache.json` file.

```
  cmake .
  sudo cmake --install .
  cp /usr/local/etc/kw-ccache.conf.example ~/.kw-ccache.conf
  # Modify ~/.kw-ccache.conf to suit your needs
```
## Authors
 - Vicente Adolfo Bolea Sanchez <vicente.bolea@gmail.com>
