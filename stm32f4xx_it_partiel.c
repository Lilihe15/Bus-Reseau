/**
  * @brief Version tronquée du fichier stm32f4xx_it.c, avec seulement l'interruption de l'UART5.
  */
void UART5_IRQHandler(void)
{
  /* USER CODE BEGIN UART5_IRQn 0 */
	HAL_UART_Receive(&huart5, buf2, 1, HAL_MAX_DELAY); /*Changer le TIMER*/
	printf("%s",buf2);
	printf("Hello World \n\r");
	HAL_UART_Receive(&huart5, buf, 1, HAL_MAX_DELAY);
	if(sizeof(buf) >= 6){
		for (int cpt = 0; 6; cpt++){
			if(buf[cpt] == '\0'){
					callType = buf[0];
					callVar = buf[4];
			}
		}
	}

	if(callType == 'G'){ // On a appelé une fonction getter.
		if(callVar == 'T'){
			BMP280_get_temperature(); // Appel la fonction de getter pour la température
		} else if(callVar == 'P'){
			BMP280_get_pressure(); // Appel la fonction de getter pour la pression
		} else if(callVar == 'K'){
			// Appeler la fonction de getter pour le coefficient K
			// Stocker le res dans une variable
			// printf
		} else if(callVar == 'A'){
			// Appeler la fonction de getter pour l'angle
			// Stocker le res dans une variable
			// printf
		} else{
			// RIEN
		}
	} else if(callVar == 'S'){
		if(callVar == 'K'){
			// BLABLABLA
		}
	}
  /* USER CODE END UART5_IRQn 0 */
  HAL_UART_IRQHandler(&huart5);
  /* USER CODE BEGIN UART5_IRQn 1 */

  /* USER CODE END UART5_IRQn 1 */
}