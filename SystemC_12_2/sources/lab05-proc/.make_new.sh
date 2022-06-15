#!/bin/sh

  path=`pwd`
  lab=`basename $path`

  rm -fr * .simvision > /dev/null 2>&1

  cp -r ../sources/${lab}/* . > /dev/null 2>&1
