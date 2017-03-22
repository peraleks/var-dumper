<?php
/**
 * Forked from symfony/var-dumper.
 *
 * @package   Peraleks\var-dumper
 * @copyright 2017 Aleksey Perevoshchikov <aleksey.perevoshchikov.n@gmail.com>
 * @license   https://github.com/peraleks/var-dumper/blob/master/LICENSE.md MIT
 * @link      https://github.com/peraleks/var-dumper
 */

namespace Symfony\Component\VarDumper\Autoload;

/**
 * Class ClassLoader.
 *
 * Автозагрузчик классов для Symfony\Component\VarDumper.
 */
class ClassLoader
{
    /**
     * Корневая директория пакета.
     *
     * @var string
     */
    private $baseDir;

    /**
     * ClassLoader constructor.
     *
     * Регистрация автозагрузчика,
     * определение корневой директории пакета.
     */
    public function __construct()
    {
        spl_autoload_register(array($this, 'loader'), false, true);
        $this->baseDir = dirname(__DIR__);
    }

    /**
     * Подключает требуемый класс.
     *
     * @param  string $className полное имя класса
     * @return void
     */
    private function loader($className)
    {
        if (0 !== strpos($className, 'Symfony\Component\VarDumper')) return;
        include
            $this->baseDir.str_replace('\\', '/', str_replace('Symfony\Component\VarDumper', '', $className)).'.php';
    }
}
