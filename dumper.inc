<?php
/**
 * Forked from symfony/var-dumper.
 *
 * @package   Peraleks\var-dumper
 * @copyright 2017 Aleksey Perevoshchikov <aleksey.perevoshchikov.n@gmail.com>
 * @license   https://github.com/peraleks/var-dumper/blob/master/LICENSE.md MIT
 * @link      https://github.com/peraleks/var-dumper
 */

use Symfony\Component\VarDumper\VarDumper;
use Symfony\Component\VarDumper\Cloner\VarCloner;
use Symfony\Component\VarDumper\Dumper\CliDumper;
use Symfony\Component\VarDumper\Dumper\DarculaHtmlDumper as Dumper;


require 'Autoload/ClassLoader.php';
new \Symfony\Component\VarDumper\Autoload\ClassLoader;


if (! function_exists('dp')) {

    function dp($var)
    {
//        if (!defined('DEVELOPMENT_MODE') || DEVELOPMENT_MODE === false) return;
        VarDumper::setHandler(function ($var) {
            $dumper = 'cli' === PHP_SAPI ? new CliDumper : new Dumper;
            $dumper->dump((new VarCloner)->cloneVar($var));
        });

        static $int = 1;

        $deb = debug_backtrace();
        $file = $deb[0]['file'];
        $line = $deb[0]['line'];

        if ('cli' === PHP_SAPI) {
            echo
                "\033[31;43m $int \033[0m".
                "\033[30;47m $file($line) \033[0m\n";
        } else {
            echo
                "<div style=\"".Dumper::STYLE['main']."\">
                <div style=\"".Dumper::STYLE['int']."\">$int</div>
                <div style=\"".Dumper::STYLE['file']."\">$file($line)</div>
                </div>
            ";
        }

        ++$int;

        VarDumper::dump($var);

    }
}
