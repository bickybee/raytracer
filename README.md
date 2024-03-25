# Ray Tracing In One Weekend

Going through [Ray Tracing In One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) to both:

1. Learn more about raytracing, which I understand conceptually but have never actually implemented myself.
2. Brush up on my vanilla C++.

# How to Build
From the root of the project, create a build folder and go from there:

```
mkdir build
cd build
cmake ..
make
```

Now you can run the program, writing the output to a ppm file:
```
./raytracer > ../images/myimage.ppm
```

MacOS can view PPM files by default. You may need to find a different solution on a different OS!

# Chapter Progress
- [x] 1. Setup
- [x] 2. Output an Image (PPM)
- [x] 3. The vec3 Class
- [x] 4. Rays, a Simple Camera, and Background
- [x] 5. Adding a Sphere
- [x] 6. Surface Normals and Multiple Objects
- [x] 7. Moving Camera Into Its Own Class
- [x] 8. Antialiasing
- [ ] 9. Diffuse Materials
- [ ] 10. Metal
- [ ] 11. Dielectrics
- [ ] 12. Positionable Camera
- [ ] 13. Defocus Blur
- [ ] 14. What Next?