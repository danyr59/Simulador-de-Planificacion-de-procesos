#include "fcfs.h"

Fcfs::Fcfs(int num_process)
{
    for(int i = 0; i < num_process; i++)
    {
        this->process_queue.push(Process(i, i));
    }
}

void Fcfs::execute()
{   
   // Tiempo original (inicio)
    auto tiempoOriginal = std::chrono::high_resolution_clock::now();

    // Duración total deseada (2 minutos = 120,000 ms)
    std::chrono::milliseconds duracionTotal(120000);

    // Iterar mientras no se alcance la duración total
    while (true) {
        // Calcular el tiempo transcurrido desde el inicio
        auto tiempoActual = std::chrono::high_resolution_clock::now();
        auto tiempoTranscurrido = std::chrono::duration_cast<std::chrono::milliseconds>(tiempoActual - tiempoOriginal);

        // Verificar si se alcanzó la duración total
        if (tiempoTranscurrido >= duracionTotal) {
            break; // Salir del bucle
        }

        // Realizar alguna acción en cada paso de tiempo
        std::cout << "Tiempo transcurrido: " << tiempoTranscurrido.count() << " ms" << std::endl;

        // Esperar un tiempo específico (por ejemplo, 1000 ms = 1 segundo)
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "Tiempo total alcanzado. Fin de la simulación." << std::endl;

    


}