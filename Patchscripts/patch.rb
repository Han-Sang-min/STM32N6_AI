require 'fileutils'

def copy_and_replace(source_path, destination_path)
  if File.exist?(destination_path)
    File.delete(destination_path)
  end
  FileUtils.copy(source_path, destination_path)
end

path = "../../STM32N6570-DK.ioc"
tx_initialize_low_level_dest = "../Core/Src/tx_initialize_low_level.S"

file_contents = File.read(path)
regexp_ide = /(ProjectManager.TargetToolchain=)(.*)/
regexp_cpuclk = /(RCC.CpuClockFreq_Value=)(\d*)/
toolchain = file_contents.match(regexp_ide)[2]
clock = file_contents.match(regexp_cpuclk)[2]

puts "The current toolchain is #{toolchain}"

if toolchain.include?("EWARM")
  puts "tx_initialize_low_level.S is correct, not replaced"
else
  copy_and_replace("../../Patchscripts/tx_initialize_low_level.S", tx_initialize_low_level_dest)
  puts "tx_initialize_low_level.S replaced with gcc version"
end

file_contents = File.read(tx_initialize_low_level_dest)
regexp_sys = /(SYSTEM_CLOCK\D*)(\d*)/
regexp_tick = /(SYSTICK_CYCLES.*\/\D)(\d*)(.*)/
file_contents.gsub!(regexp_sys, "\\1#{clock}")
file_contents.gsub!(regexp_tick, "\\11000\\3")

File.open(tx_initialize_low_level_dest, "w") do |file|
  file.write(file_contents)
end

puts "tx_initialize_low_level.S patched for correct systick frequency"