#pragma once

namespace Primitives {
	const float TRIANGLE[6] = {
		0.f, .5f,
		.5, -.5f,
		-.5f, -.5f
	};

	const float QUAD_WITHOUT_EBO[12] = {
		.5f, .5f,
		.5, -.5f,
		-.5f, -.5f,
		-.5f, .5f,
		.5, .5f,
		-.5f, -.5f
	};

	// needs QUAD_EBO & glDrawElements
	const float QUAD[8] = {
		.5f, .5f,    // top right    - 0
		.5, -.5f,    // bottom right - 1
		-.5f, -.5f,  // bottom left  - 2
		-.5f, .5f,   // top left     - 3

		//.5, .5f,
		//-.5f, -.5f
	};

	const float QUAD_EBO[6] = {
		0, 1, 3, 1, 2, 3
	};
}