#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = log_create("tp0.log", "TP0", 1 , LOG_LEVEL_INFO);
	log_info(logger, "Hola! Soy un Log");
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

    config = config_create("cliente.config");
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	valor = config_get_string_value(config, "CLAVE");
    log_info(logger,"Leí la IP: %s", ip);
	log_info(logger,"Leí el Puerto: %s", puerto);
    log_info(logger,"Leí el Valor: %s", valor);
    
	config_destroy(config);
	log_destroy(logger);
	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
    send(conexion, valor, strlen(valor) + 1, 0);
	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;
	// La primera te la dejo de yapa
	while (1) {
        // Leer una línea desde la consola
        leido = readline("> ");
        // Verificar si se ha leído una línea vacía
        if (strcmp(leido, "") == 0) {
            free(leido); // Liberar la memoria antes de salir
            break; // Salir del bucle si la línea está vacía
        }
        // Loguear la línea leída
        log_info(logger, "Leído: %s", leido);
        // Liberar la memoria de la línea leída
        free(leido);
    } 
}


void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete;

	// Leemos y esta vez agregamos las lineas al paquete
    while ((leido = readline("> ")) != NULL) {
           if (strlen(leido) == 0) {
               free(leido);
               break;
           }
           agregar_a_paquete(paquete, leido, strlen(leido)+1);
           free(leido);
       }
       enviar_paquete(paquete, conexion); 
    
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	 eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	close(conexion);
	log_destroy(logger);
	config_destroy(config);

	exit(0);
}
