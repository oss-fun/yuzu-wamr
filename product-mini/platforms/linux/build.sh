#!/bin/bash

cmake .. -DWAMR_BUILD_REF_TYPES=1 -DWAMR_BUILD_FAST_INTERP=0 && make -j

