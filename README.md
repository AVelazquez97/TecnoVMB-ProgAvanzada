## Laboratorio 4 - Implementación | Programación Avanzada - 2023

Este es un proyecto universitario realizado por los siguientes integrantes:

- [Natalia López](https://github.com/Natalialopezutec)
- [Ignacio Fernández](https://github.com/ignfer)
- [Luciano Rosa](https://github.com/cocoamaker)
- [Alexis Velázquez](https://github.com/AVelazquez97)

NOTA:
Cuando se actualiza la fecha de sistema, se verifican todas las reservas y en caso de que la fecha sea mayor que la fecha de checkout de una reserva y ademas
dicha reserva no tenga ninguna estadia, es decir, nadie se presento, la reserva pasa a tener el estado CANCELADA. 
De forma analoga, cuando se actualiza la fecha sistema tambien se checkean las reservas CANCELADAS y en caso de que la fecha actual sea menor a la de checkout
de la reserva, se vuelve a poner como ABIERTA o CERRADA dependiendo si la misma tenia estadias o no.

Esto explica el porque al cargar los datos de prueba se pueden ver reservas CANCELADAS y se le recomienda al usuario final que tenga esto presente a la hora
de probar el programa.