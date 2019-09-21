#include "AppClass.h"
void Application::InitVariables(void)
{
	
	// generate cubes and store them in a vector
	for (int i = 0; i < numOfCubes; i++)
	{
		m_pMeshes.push_back(new MyMesh());
		m_pMeshes[i]->GenerateCube(sizeOfCubes, C_BLACK);
	}

	// create each transformation using the shape of the object 2d array
	for (int i = 0; i < heightOfShape; i++)
	{
		for (int j = 0; j < widthOfShape; j++)
		{
			if (shapeOfObject[i][j] == 1)
			{
				// shift the values so the object is centered
				m_pTransformations.push_back(vector3(sizeOfCubes * (j - (widthOfShape / 2)), sizeOfCubes * ((heightOfShape / 2) - i), 0.0f));
			}
		}
	}
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Adjust Offset
	if (movingRight)
	{
		offset.x += 0.01;
		if (offset.x >= 7)
		{
			movingRight = false;
		}
	}
	else
	{
		offset.x -= 0.01;
		if (offset.x <= -7)
		{
			movingRight = true;
		}
	}
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// draw each mesh onto the screen with their corresponding transformations
	for (int i = 0; i < numOfCubes; i++)
	{
		m_pMeshes[i]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), 
			glm::translate(IDENTITY_M4, m_pTransformations[i] + offset));
	}
		
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	for (int i = 0; i < numOfCubes; i++)
	{
		delete m_pMeshes[i];
		m_pMeshes[i] = nullptr;
	}

	//release GUI
	ShutdownGUI();
}