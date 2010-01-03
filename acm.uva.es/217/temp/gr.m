p1 = {6.0, 7.0};
p2 = {2.0, 4.0};
Show[Graphics[{
      Disk[p1, 0.1],
      Disk[p2, 0.1],
      Line[{{0, -5}, {0, 10}}],
      Line[{{-5, 0}, {10, 0}}],
      Hue[0],
      Line[{
          -5{Cos[(90 - 116.5651) Degree], Sin[(90 - 116.5651 )Degree]},
          5{Cos[(90 - 116.5651) Degree], Sin[(90 - 116.5651) Degree]}
          }],
      RGBColor[0, 0, 0],
      Line[{
          
          p1 - 5{Cos[(90 - 116.5651 - 126.8699)Degree], Sin[(90 - 116.5651 - 
              126.8699)Degree]},
          p1 + 5{Cos[(90 - 116.5651 - 126.8699)Degree], Sin[(
          90 - 116.5651 - 126.8699)Degree]}
          }],
      Line[{
          p2 - 5{
                      Cos[(90 - 116.5651 - 319.3987)Degree], Sin[(90 - \
116.5651 - 319.3987)Degree]},
          p2 + 5{Cos[(90 - 116.5651 - 319.3987)Degree], 
      Sin[(90 - 116.5651 - 319.3987)Degree]}
          }],
      Hue[0.7],
      Disk[{6, 5}, 0.1],
      Hue[0.6],
      Line[{
          {6, 5} - 
                        2.2361{Cos[(90 - 116.5651) Degree], Sin[(90 - \
116.5651 )Degree]},
          {6, 
          5} + 2.2361{Cos[(90 - 116.5651) Degree], Sin[(90 - 
                116.5651) Degree]}
          }]
      }], AspectRatio -> 1]
