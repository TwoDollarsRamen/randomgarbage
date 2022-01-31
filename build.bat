@echo off

for %%f in (*.cpp) do (
	cl %%f
)

for %%f in (*.c) do (
	cl %%f
)