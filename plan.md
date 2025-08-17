## Phase 1: Foundation & Math (Days 1-4)

### Day 1: Project Setup & Math Fundamentals
**Morning (4h): Core Math Library**
- **Resources**: 
  - "3D Math Primer for Graphics" (chapters on vectors)
  - Khan Academy Linear Algebra (vectors, dot product, cross product)
- **Implementation Strategy**:
  - Start with basic vector operations (add, subtract, multiply)
  - Use pen and paper first - draw vectors, visualize operations
  - Test each function with known inputs/outputs
  - Build incrementally: basic ops → normalization → dot/cross products

**Afternoon (4h): Ray Mathematics**
- **Resources**: 
  - "Ray Tracing in One Weekend" (first 2 chapters)
  - Scratchapixel.com ray-tracing basics
- **Think About**: 
  - A ray is just origin + direction * t
  - Practice parametric equations on paper
  - Understand what t represents (distance along ray)

### Day 2: Basic Scene Structures
**Morning (4h): Scene Data Structures**
- **Strategy**:
  - Define structures on paper first
  - Think about memory layout with your arena allocator
  - Consider: what's the minimum data needed for each object?
  - Start simple - just position, color, basic properties

**Afternoon (4h): Arena Integration**
- **Focus**: 
  - Write helper functions for common allocations
  - Pattern: allocate → initialize → link into scene
  - Test memory usage patterns
  - Practice: allocate objects, reset arena, allocate again

### Day 3: Intersection Mathematics  
**Morning (4h): Sphere Intersection**
- **Resources**:
  - "Real-Time Rendering" chapter on ray-object intersection
  - Derive the math yourself with quadratic equation
- **Process**:
  - Work out sphere intersection on paper
  - Understand discriminant (no hit, tangent, two hits)
  - Code step by step, test with known cases
  - Visualize: draw sphere, ray, intersection points

**Afternoon (4h): Plane Intersection**
- **Strategy**:
  - Much simpler than sphere - just dot products
  - Understand plane equation: dot(point - plane_point, normal) = 0
  - Test edge cases: ray parallel to plane, ray starting on plane

### Day 4: Cylinder Intersection (Complex)
**Full Day (8h): Cylinder Math**
- **Resources**: 
  - Graphics Gems or similar for cylinder intersection
  - Break into: infinite cylinder + cap tests
- **Approach**:
  - Don't rush this - it's the hardest intersection
  - Work in 2D first (circle-line intersection)
  - Then extend to 3D cylinder
  - Handle caps separately
  - Test extensively with simple cases

## Phase 2: Parser Implementation (Days 5-7)

### Day 5: Parser Foundation
**Morning (4h): Tokenization**
- **Strategy**:
  - Build simple lexer: identify numbers, identifiers, commas
  - Use state machine approach
  - Test with malformed input early
  - Focus on robust number parsing (handle negatives, decimals)

**Afternoon (4h): Basic Element Parsing**
- **Process**:
  - Start with simplest element (ambient light)
  - Pattern: read identifier → dispatch → parse parameters
  - Build error reporting as you go
  - Test each element type individually

### Day 6: Complete Parser
**Morning (4h): All Element Types**
- **Focus**: 
  - Camera, lights, sphere, plane parsing
  - Validate ranges as you parse
  - Use your arena for all temporary data

**Afternoon (4h): Error Handling & Validation**
- **Strategy**:
  - Collect errors, don't stop at first one
  - Provide line/column information
  - Test with deliberately broken files
  - Validate scene completeness (one camera, one ambient)

### Day 7: Parser Testing & Refinement
**Full Day (8h): Robustness**
- **Activities**:
  - Create comprehensive test suite
  - Edge cases: empty files, malformed numbers, missing fields
  - Memory leak testing with arena resets
  - Performance testing with large scenes

## Phase 3: Core Ray Tracing (Days 8-11)

### Day 8: Camera & Ray Generation
**Morning (4h): Camera Mathematics**
- **Resources**: 
  - Understanding camera FOV and aspect ratio
  - "Ray Tracing in One Weekend" camera chapter
- **Process**:
  - Start with simple perspective projection
  - For each pixel, generate ray from camera through pixel
  - Test: rays should diverge correctly based on FOV

**Afternoon (4h): Basic Ray Tracing Loop**
- **Structure**:
  - For each pixel: generate ray → find closest intersection → calculate color
  - Start with just intersection testing (no lighting)
  - Output simple colors based on which object hit

### Day 9: Lighting Model Implementation
**Morning (4h): Ambient + Diffuse Lighting**
- **Resources**: 
  - Phong lighting model explanation
  - Understand Lambert's cosine law for diffuse lighting
- **Process**:
  - Start with ambient (constant color)
  - Add diffuse: dot(surface_normal, light_direction)
  - Clamp values, handle multiple lights

**Afternoon (4h): Shadows**
- **Strategy**:
  - For each light: cast shadow ray from hit point to light
  - If ray hits object before reaching light → in shadow
  - Add small epsilon to avoid self-intersection

### Day 10: Complete Lighting
**Morning (4h): Multiple Lights & Color Mixing**
- **Focus**:
  - Accumulate lighting from all light sources
  - Handle color blending correctly
  - Test with various light configurations

**Afternoon (4h): Cylinder Integration**
- **Challenge**: 
  - Integrate your cylinder intersection code
  - Test thoroughly - cylinders are tricky
  - Handle edge cases (ray hitting caps vs sides)

### Day 11: Optimization & Debugging
**Full Day (8h): Polish Core Engine**
- **Activities**:
  - Profile rendering performance
  - Fix any intersection bugs
  - Optimize hot paths (intersection tests)
  - Ensure numerical stability

## Phase 4: Integration & Display (Days 12-14)

### Day 12: MLX Integration
**Morning (4h): Window Management**
- **Resources**: 
  - MLX documentation
  - Simple MLX examples
- **Strategy**:
  - Start with opening window, displaying solid color
  - Understand MLX pixel format (likely ARGB)
  - Convert your float colors to integer pixels

**Afternoon (4h): Image Display**
- **Process**:
  - Render to your image buffer
  - Copy buffer to MLX image
  - Display in window
  - Test with simple scenes

### Day 13: Event Handling & Polish
**Morning (4h): User Input**
- **Implementation**:
  - ESC key to exit
  - Window close button
  - Basic error handling for MLX functions

**Afternoon (4h): Integration Testing**
- **Focus**:
  - Test complete pipeline: file → parse → render → display
  - Create test scenes for each feature
  - Memory leak testing

### Day 14: Final Polish & Testing
**Morning (4h): Bug Fixes & Edge Cases**
- **Activities**:
  - Test with subject's example scenes
  - Handle error cases gracefully
  - Performance optimization

**Afternoon (4h): Documentation & Submission Prep**
- **Tasks**:
  - Clean up code
  - Test Makefile
  - Prepare demo scenes
  - Final testing

## Learning Strategy Throughout:

### Daily Practices:
1. **Start each day by drawing/sketching the math** you're about to implement
2. **Test incrementally** - don't write large functions without testing parts
3. **Use simple test cases** - start with rays hitting objects at origin
4. **Debug visually** - output intermediate values, use simple scenes
5. **Read code aloud** to catch logic errors

### When Stuck:
1. **Break the problem smaller** - what's the simplest version?
2. **Work examples by hand** - trace through the math manually
3. **Use pen and paper** - draw diagrams of what should happen
4. **Test with trivial cases** - sphere at origin, ray along axis
5. **Ask peers for code review** - fresh eyes catch bugs

### Key Resources:
- **"Ray Tracing in One Weekend"** - free PDF, excellent tutorial
- **Scratchapixel.com** - comprehensive computer graphics tutorials  
- **"Real-Time Rendering"** - reference for intersection algorithms
- **Khan Academy** - for math fundamentals
- **Your peers** - for debugging and understanding checks

### Success Metrics:
- **Week 1**: Can parse files and intersect rays with spheres
- **End of Day 10**: Can render a simple scene with lighting
- **End of Day 13**: Complete working raytracer with MLX display

This timeline is aggressive but achievable if you stay focused and build incrementally. The key is not getting stuck on perfect code - get it working first, then optimize.
